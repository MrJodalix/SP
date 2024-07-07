/**
 * Implementierung der Indizierung von beliebigen Dateien
 *
 * @author mhe, mre, tti, Joshua-Scott Schöttke, Ilana Schmara, Gruppe 21
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "indexer.h"

#ifndef VALIDCHAR
#define VALIDCHAR(sign) (((sign) >= 'A' && (sign) <= 'Z') || ((sign) >= 'a' && (sign) <= 'z'))
#endif

/**
 * Hilfsfunktion zur Ueberpruefung von einzelnen Zeichen
 * 
 * @param[in] sign Zeichen welches ueberprueft werden soll
 * 
 * @return 0 || !0
 
int
validChar(char sign) {
  return ();
}
 */
/**
 * Liest aus dem uebergebenen Stream und ueberliest dabei alle Zeichen ausser
 * denen, die zu einem Wort gehoeren, also alle Klein- und Grossbuchstaben. Wird
 * hierbei ein zu einem Wort gehoeriges Zeichen z gefunden, so wird das Ueberlesen
 * beendet und das zuletzt gefundene Zeichen z wieder zurueck in den Stream
 * geschrieben. Zeilenumbrueche werden zwar auch ueberlesen, aber gleichzeitig
 * wird die Anzahl der ueberlesenen Zeilenumbrueche ueber newlines kommuniziert.
 *
 * Die Funktion darf nicht mit einem Stream aufgerufen werden, der bereits das
 * Dateiende ueberschritten hat.
 *
 * @param[in/out] stream   Zeiger auf den Eingabestream
 * @param[out]    newlines Anzahl der ueberlesenen Zeilenumbrueche
 *
 * @return ERR_NULL || ERR_READ_STREAM
 *
 * @pre stream != NULL
 * @pre !feof(stream)
 * @pre newlines != NULL
 */
static ErrorCode
skip(FILE * stream, unsigned int * newlines) {
  assert(stream != NULL);
  assert(!feof(stream));
  assert(newlines != NULL);
  
  ErrorCode
    error = ERR_NULL
  ;
  
  int  
    readChar = 0
  ;
  
  while ((!error && (readChar = fgetc(stream)) != EOF) 
      && (!VALIDCHAR(readChar))) {
      
    if (readChar == '\n') {
      (*newlines)++;
    }
    
  }
  
  if (ferror(stream) != 0) {
    error = ERR_READ_STREAM;
  }
  
  //Buchstabe zurück in den Stream schreiben
  if ( !error && readChar != EOF ) {
    if ( (ungetc((char)readChar, stream) == EOF) ) {
      error = ERR_READ_STREAM;
    }
  }
  
  
  return error;
}

/**
 * Liest aus dem uebergebenen Stream ein einzelnes Wort bestehend aus Klein- und
 * Grossbuchstaben in einen Puffer ein. Der Puffer nebst seiner Groesse bei Aufruf
 * von readWord wird vom Aufrufer per Parameter buffer und bufsize uebergeben.
 *
 * Der Puffer darf die Groesse 0 haben, in diesem Fall muss *buffer dem NULL-Zeiger
 * entsprechen. Sofern der Puffer nicht ausreichend gross fuer das einzulesende
 * Wort ist, wird er von readWord geeignet vergroessert. Die neue Groesse des
 * Puffers (die groesser als fuer das Wort erforderlich ausfallen darf) und der
 * moeglicherweise neue Anfangszeiger des Puffers wird dem Aufrufer ueber die
 * Parameter buffer und bufsize zurueckgemeldet. 
 *
 * Die Laenge des gelesenen Wortes
 * wird ueber den Parameter wordsize zurueckgemeldet.
 *
 * Die Funktion readWord erzeugt im Puffer ein leeres Wort, wenn sie im Stream
 * unmittelbar auf ein Trennzeichen trifft.
 *
 * Die Funktion darf nicht mit einem Stream aufgerufen werden, der bereits das
 * Dateiende ueberschritten hat.
 *
 * Wird beim Einlesen ein Trennzeichen t gefunden, so wird das Einlesen beendet
 * und das zuletzt gefundene Zeichen t wieder zurueck in den Stream geschrieben.
 *
 * @param[in/out] stream   Zeiger auf den Eingabestream
 * @param[in/out] buffer   Zeiger auf einen Pufferanfangszeiger
 * @param[in/out] bufsize  Zeiger auf die Groesse des Puffers buffer
 * @param[out]    wordsize Zeiger auf die Laenge des eingelesen Wortes
 *
 * @return ERR_NULL || ERR_READ_STREAM
 *
 * @pre stream != NULL
 * @pre !feof(stream)
 * @pre buffer != NULL
 * @pre bufsize != NULL
 * @pre (*buffer != NULL) == (*bufsize > 0)
 * @pre wordsize != NULL
 */
static ErrorCode
readWord(FILE * stream, char ** buffer, unsigned int * bufsize,
    unsigned int * wordsize) {
  assert(stream != NULL);
  assert(!feof(stream));
  assert(buffer != NULL);
  assert(bufsize != NULL);
  assert((*buffer != NULL) == (*bufsize > 0));
  assert(wordsize != NULL);
  
  ErrorCode
    error = ERR_NULL
  ;
  
  int
    readChar = '\0'
  ;
  
  unsigned int
    length = 0
  ;
  
  while (!error && ( (readChar = fgetc(stream) ) != EOF ) 
      && (VALIDCHAR(readChar))){ 
    if (length < *bufsize) {
      //an der Stelle von length wird das aktuelle Zeichen gespeichert
      (*buffer)[length++] = readChar;
      (*wordsize)++;
    } else if (length >= *bufsize) {
      //nicht genug Speicherplätze im Puffer, Puffer vergroessern
      *bufsize += (length + 1);
      (*buffer) = realloc(*buffer, (sizeof(char)) * (*bufsize));  
      
      if((*buffer) == NULL) {
        error_print(stderr, ERR_OUT_OF_MEMORY);
        exit(ERR_OUT_OF_MEMORY);
      }
      
      (*buffer)[length++] = readChar;
      (*wordsize)++;
    } else {
      error = ERR_READ_STREAM;
    }
  } 
   //Ende des Wortes markieren  
  (*buffer)[length++] = '\0';
    
  if (ferror(stream) != 0) {
    error = ERR_READ_STREAM;
  }
  
  //Trennzeichen zurück in den Stream schreiben
  
  if ( !error && readChar != EOF ) {
    if ( (ungetc((char)readChar, stream) == EOF) ) {
      error = ERR_READ_STREAM;
    }
  }
  return error;
}

/**
 * Erzeugt zum Eingabestream stream einen Index. Initial ist dazu ein Zeiger auf
 * einen leeren Index zu uebergeben. Nach Ablauf der Funktion zeigt der Zeiger
 * index auf den fertig erzeugten Index zu stream.
 *
 * Im Stream werden Woerter nach folgenden Regeln erkannt: Ein Wort ist eine
 * mindestens einelementige Zeichenfolge, die lediglich aus Klein- und
 * Grossbuchstaben (ASCII), also 'a' bis 'z' und ' A' bis 'Z', besteht.
 * Zwei Woerter werden durch eine mindestens einelementige Folge von Trennzeichen
 * getrennt, wobei Trennzeichen alle Zeichen (bzw. Bytewerte) sind, die nicht
 * in Woertern vorkommen koennen. Folgen von Trennzeichen koennen auch am Anfang
 * oder Ende des streams auftreten (muessen aber nicht). Zeilenumbrueche sind
 * Trennzeichen, die zugleich die Angabe zur Zeile, in der ein Wort vorkommt,
 * steuern. Als Zeilenumbruch wird ausschliesslich der Unix-Zeilenumbruch '\\n'
 * gewertet.
 *
 * Es werden lediglich Woerter mit einer Mindestlaenge von min und einer
 * Maximallaenge max in den Index aufgenommen. Woerter, die kuerzer oder laenger
 * sind werden ohne Signalisierung eines Fehlers ueberlesen.
 *
 * @param[in/out] stream der Dateistream
 * @param[out]    index  Zeiger auf einen Index
 * @param         min    kuerzeste zu indizierende Wortlaenge
 * @param         min    laengste zu indizierende Wortlaenge
 *
 * @return ERR_NULL || ERR_READ_STREAM
 *
 * @pre stream != NULL
 * @pre index ist ein Zeiger auf einen leeren Index
 * @pre min >= 1
 * @pre max >= min
 */
ErrorCode
index_make(FILE * stream, Index * index, unsigned long min, unsigned long max) {
  assert(stream != NULL);
  assert(wordlist_isEmpty(*index));
  assert(min >= 1);
  assert(max >= min);
  
  ErrorCode
    error = ERR_NULL
  ;
  
  unsigned int
    newlines = 0,
    position = 0,
    wordsize = 0,
    bufsize = min
  ;
  
  Word
    buffer = NULL
  ;
    
  Occurrence
    occCount = { .line = 0, .pos = 0 }
  ;
  
  buffer = malloc(bufsize * sizeof(char));  
  if(buffer == NULL) {
    error_print(stderr, ERR_OUT_OF_MEMORY);
    exit(ERR_OUT_OF_MEMORY);
  }
  
  while(!error && !feof(stream)) {
    if (!feof(stream)) {
      //Wort einlesen in Puffer
      wordsize = 0;

      error = readWord(stream, &buffer, &bufsize, &wordsize);
      //Nur bestimmte Woerter betrachten
      if((!error) && (wordsize >= min) && (wordsize <= max)) {
      
        //bei einer neuen Zeile: Position auf 0 setzen
        if (occCount.line != newlines) {
          position = 0;
        }
        occCount.line = newlines;
        occCount.pos = position++;
        //alle Wörter in Wortliste hinzufuegen
        *index = wordlist_insert(*index, word_copy(buffer), occCount);
      }
    }
    
    if (!feof(stream)) {
      error = skip(stream, &newlines);
    }
  }
    
  free(buffer);
  buffer = NULL;
  
  if ( stream != NULL && fclose(stream) != 0 ) {
    error = ERR_READ_STREAM;
  }
  stream = NULL;
  return error;
}

/**
 * Gibt den uebergebenen Index auf dem uebergebenen stream im CSV-Format aus.
 * Je Wort und Vorkommen des Wortes wird dazu eine Zeile erzeugt.
 *
 * Dabei besteht eine Zeile immer aus (ohne Leerzeichen):
 * Wort,Zeile,Position
 *
 * Die Sortierung der Woerter und Wortvorkommen entspricht hierbei der Sortierung
 * der entsprechenden Listen. D.h. z.B., dass die Zeilen zu den Vorkommen eines
 * Wortes in einem Block nacheinander ausgegeben werden (entsprechend der
 * Sortierung der Vorkommen).
 *
 * Als Zeilenumbruch wird der Unix-Zeilenumbruch '\\n' verwendet. Nach jeder Zeile
 * einschliesslich der letzten Zeile wird ein Zeilenumbruch ausgegeben. Daraus
 * folgt, dass im Falle des leeren Index nichts ausgegeben wird.
 *
 * @param[in] stream der Dateistream
 * @param[in] index  der Index
 *
 * @return ERR_NULL || ERR_WRITE_STREAM
 *
 * @pre stream != NULL
 */
ErrorCode
index_printCSV(FILE * stream, Index index) {
  assert(stream != NULL);
  
  ErrorCode
    error = ERR_NULL
  ;
  
  OccList
    run = NULL
  ;
  
  while (!error && index != NULL) {
    run = index->payload.occlist;
    while (run != NULL) {
      if( fprintf(stream,"%s,%lu,%d\n", index->payload.word
                                      , run->elements.line
                                      , run->elements.pos) >= 0 ) {
        run = run->next; 
      } else {
        error = ERR_WRITE_STREAM;
      }
    }
    
    index = index->next;
  }
  
   
  return error;
}

/**
 * Gibt den uebergebenen Index auf dem uebergebenen stream in einem fuer
 * Menschen gut lesbaren Format aus.
 *
 * @param[in] stream der Dateistream
 * @param[in] index  der Index
 *
 * @return ERR_NULL || ERR_WRITE_STREAM
 *
 * @pre stream != NULL
 */
ErrorCode
index_printPretty(FILE * stream, Index index) {
  assert(stream != NULL);
  
  ErrorCode
    error = ERR_NULL
  ;
  
  OccList
    run = NULL
  ;
    
  while (!error && index != NULL && index->payload.word != NULL) {
    fprintf(stream,"%s\n", index->payload.word);
    run = index->payload.occlist;
    while (run != NULL) {
      if( fprintf(stream,"  |- Line%lu, Pos%d\n", run->elements.line
                                                , run->elements.pos) >= 0 ) {
        run = run->next;
      } else {
        error = ERR_WRITE_STREAM;
      }
    }
    index = index->next;
  }
  
  return error;
}

/**
 * Loescht den Index und gibt den durch ihn belegten Speicher wieder frei.
 * Der uebergebene Index darf danach nicht mehr verwendet werden.
 *
 * @param[in] index zu loeschender Index
 *
 * @return leerer Index
 */
Index
index_delete(Index index) { 
  wordlist_delete((index));
  return wordlist_empty();
}

/**
 * Implementierung der Liste von Woertern und ihren Vorkommen
 *
 * @author mhe, mre, tti, Joshua-Scott Schöttke, Ilana Schmara, Gruppe 21
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "wordlist.h"
#include "error.h"

/** Referenzaehler fuer die gespeicherten Wortlistenelemente */
int wordlist_refs = 0;

/**
 * Erzeugt eine leere Liste.
 * Da eine Liste nur ein Zeiger auf ein Element ist, ist die leere Liste der
 * Nullzeiger.
 *
 * @return Leere Liste
 */
WordList
wordlist_empty() {
  return NULL;
}

/**
 * Prueft ob die Liste leer ist.
 *
 * @param[in] l Zu pruefende Liste
 *
 * @return True, wenn die Liste leer ist, sonst false
 */
int
wordlist_isEmpty(WordList l) {
  return l == wordlist_empty();
}

/**
 * Liefert das Wort am Kopf der Liste.
 *
 * @param[in] l Liste
 *
 * @return Wort des ersten Elements
 *
 * @pre Die Liste darf nicht leer sein.
 */
Word
wordlist_head_word(WordList l) {
  assert(!wordlist_isEmpty(l));
  return l->payload.word;
}

/**
 * Liefert die Vorkommensliste am Kopf der uebergebenen Liste.
 *
 * @param[in] l Liste
 *
 * @return Liste von Vorkommen
 *
 * @pre Die Liste darf nicht leer sein.
 */
OccList
wordlist_head_occs(WordList l) {
  assert(!wordlist_isEmpty(l));
  
  return l->payload.occlist;
}


/**
 * Liefert die Liste ohne das Kopf-Element.
 *
 * @param[in] l Liste
 *
 * @return Der Rest
 *
 * @pre Die Liste darf nicht leer sein.
 */
WordList
wordlist_tail(WordList l) {
  assert(!wordlist_isEmpty(l));
  
  return l->next;
}

/**
 * Fuegt das Element (Wort & Vorkommen) vorne an der Liste an und gibt einen
 * Zeiger auf den neuen Listenanfang zurueck.
 *
 * Das Wort bzw. die Vorkommensliste werden nicht kopiert. Fuer die spaetere
 * Speicherfreigabe des Wortes und der Vorkommensliste ist die Wortliste
 * verantwortlich.
 *
 * @param[in] l    Wortliste
 * @param[in] word das Wort
 * @param[in] occs Die Liste mit den Vorkommen des Wortes
 *
 * @return veraenderte Liste
 *
 * @pre word != NULL
 * @pre occs ist nicht leer
 */
WordList
wordlist_cons(WordList l, Word word, OccList occs) {
  
  assert(word != NULL);
  assert(!occlist_isEmpty(occs));
    
  WordList result = malloc( sizeof(struct WordListNode) );
    
  wordlist_refs++;
  
  if(result == NULL) {
    error_print(stderr, ERR_OUT_OF_MEMORY);
    exit(ERR_OUT_OF_MEMORY);
  }
  
  result->payload.word = word;
  result->payload.occlist = occs;
  result->next = l;
  return result;
}

/**
 * Fuegt das Vorkommen eines Wortes in die Liste ein. Falls das Wort noch nicht
 * vorhanden ist, wird das Wort aufsteigend sortiert, entsprechend des
 * Ergebnisses von strcmp, mit seinem Vorkommen in die Liste eingefuegt. Sofern
 * das Wort schon enthalten ist, wird das Vorkommen entsprechend der Sortierung
 * von occlist_insert in die Vorkommensliste des bereits vorhandenen Wortes
 * eingefuegt.
 *
 * Die Funktion gibt den Zeiger auf die veraenderte Liste zurueck.
 *
 * Das Wort wird nicht kopiert.
 * Fuer die spaetere Speicherfreigabe des Wortes ist die Wortliste
 * verantwortlich.
 *
 * @param[in] l   Liste
 * @param[in] w   das Wort
 * @param[in] occ Vorkommen des Wortes
 *
 * @return veraenderte Liste
 *
 * @pre word != NULL
 */
WordList
wordlist_insert(WordList l, Word word, Occurrence occ) {  
  assert(word != NULL);
  //Abbruchvariable
  int inserted = 1;
  //Iterationsvariable
  WordList run = l;
  
  OccList start = NULL;
  
  //Wenn Liste leer
  if (l == NULL) {
    //erstellt den ersten Knoten der Liste mit der neuen occlist
    l = wordlist_cons(l, word, occlist_insert(start, occ));
  } else {
    //Liste durchlaufen bis gleiches oder groesseres Wort (ASCII-Wert)
    
    while ( run != NULL && inserted != 0 ) {
      //ueberprueft auf Ende der Liste
      if ( run->next == NULL ) {
        if ( strcmp(run->payload.word, word) < 0 ) {
          run->next = wordlist_cons(run->next, word, (occlist_insert(start, occ)));
          inserted = 0;
        } else if ( strcmp(run->payload.word, word) == 0 ) {
          //Wort bereits in Liste enthalten
          run->payload.occlist = occlist_insert(run->payload.occlist, occ);
          //freigeben des Speichers fuer das Wort
          word = word_delete(word);
          inserted = 0;
        } else {
          l = wordlist_cons(l, word, (occlist_insert(start, occ)));
          inserted = 0;
        }
      } else {
        //ueberpruft ob word zwischen zwei Worten in der Liste liegt
        if ( (strcmp(run->payload.word, word) < 0) && (strcmp(run->next->payload.word, word) > 0)) {
          run->next = wordlist_cons(run->next, word, (occlist_insert(start, occ)));
          inserted = 0;
        } else if ( strcmp(run->payload.word, word) == 0 ) {
          run->payload.occlist = occlist_insert(run->payload.occlist, occ);
          word = word_delete(word);
          inserted = 0;
        }
      }
      run = run->next;
    }
  }
  return l;
}

/**
 * Hilfsfunktion
 * Loescht das Kopfelement aus einer Liste und gibt den belegten Speicher wieder frei.
 * 
 *
 * @param[in] l Liste
 *
 * @return Liste um ein Element verringert
 *
 * @pre Liste darf nicht leer sein
 */
WordList 
deleteFirstWord(WordList l) {
    
  assert( !wordlist_isEmpty(l) );
  
  WordList res = wordlist_tail(l);
  occlist_delete(l->payload.occlist);
  word_delete(l->payload.word);
  free( l );
  wordlist_refs--;
  return res;
  
}
/**
 * Loescht die gesamte Liste und gibt ihren belegten Speicher wieder frei.
 * Die uebergebene Liste darf danach nicht mehr verwendet werden.
 *
 * @param[in/out] l Liste
 *
 * @return leere Liste
 */
WordList
wordlist_delete(WordList l) {
  while( !wordlist_isEmpty(l) ) {
    l = deleteFirstWord(l);
  }
  return wordlist_empty();
}


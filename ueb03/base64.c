/**
 * @file base64.c
 * 
 * Implementierung des Base64-Moduls
 * 
 * @author aan, avh, mhe, mre, tti, Joshua-Scott Schöttke, Ilana Schmara Gruppe 21
 */

#include <assert.h>
 
#include "base64.h"

/** Base64-Zeichensatz */
unsigned char base64[] = {
  'A','B','C','D','E','F','G','H',
  'I','J','K','L','M','N','O','P',
  'Q','R','S','T','U','V','W','X',
  'Y','Z','a','b','c','d','e','f',
  'g','h','i','j','k','l','m','n',
  'o','p','q','r','s','t','u','v',
  'w','x','y','z','0','1','2','3',
  '4','5','6','7','8','9','+','/'
};

/**
 * Kodiert eine Binaerdatei mit Base64 zu einer ASCII-Textdatei.
 * 
 * @param char * source Dateiname der Quelldatei
 * @param char * dest Dateiname der Zieldatei
 * @pre source != NULL 
 * @pre dest != NULL
 * @return ErrorSet mit moeglichen Fehlercodes:
 *  - ERR_B64_ENCODE Ein Fehler ist aufgetreten.
 *  - ERR_SOURCE_FILE Fehler beim Oeffnen oder Lesen der Quelldatei
 *  - ERR_DESTINATION_FILE Fehler beim Oeffnen oder Beschreiben der Zieldatei
 */
ErrorSet
base64_encodeFile(char * source, char * dest) {
  assert (source != NULL);
  assert (dest != NULL);
  
  ErrorSet
    error = ERR_NULL
  ;
  
  FILE 
    * readFile = NULL,
    * destFile = NULL
  ;
  
  readFile = fopen(source, "rb"); 

  destFile = fopen(dest, "wb"); 
  
  if (readFile == NULL && destFile == NULL) {
    error |= ERR_DESTINATION_FILE;
    error |= ERR_SOURCE_FILE;
    error |= ERR_B64_ENCODE;
  } else if (readFile == NULL) {
    error |= ERR_SOURCE_FILE;
    error |= ERR_B64_ENCODE;
  } else if (destFile == NULL) {
    error |= ERR_DESTINATION_FILE;
    error |= ERR_B64_ENCODE;
  } else {
  
    error = base64_encodeStream(readFile, destFile);

  }    
  
  if ( readFile != NULL && fclose(readFile) != 0 ) {
    error |= ERR_SOURCE_FILE;
    error |= ERR_B64_ENCODE;
  }
  readFile = NULL;
  
  if ( destFile != NULL && fclose(destFile) != 0 ) {
    error |= ERR_DESTINATION_FILE;
    error |= ERR_B64_ENCODE;
  }
  destFile = NULL;
  
  return error;
}

/**
 * Dekodiert eine mit Base64 kodierte Quelldatei zu einer Binaerdatei.
 * 
 * @param char * source Dateiname der Quelldatei
 * @param char * dest Dateiname der Zieldatei
 * @pre source != NULL 
 * @pre dest != NULL
 * @return ErrorSet mit moeglichen Fehlercodes:
 *  - ERR_B64_DECODE Ein Fehler ist aufgetreten.
 *  - ERR_SOURCE_FILE Fehler beim Oeffnen oder Lesen der Quelldatei
 *  - ERR_DESTINATION_FILE Fehler beim Oeffnen oder Beschreiben der Zieldatei
 */
ErrorSet
base64_decodeFile(char * source, char * dest) {
  assert (source != NULL);
  assert (dest != NULL);
  
  ErrorSet
      error = ERR_NULL
  ;
    
  FILE 
    * readFile = NULL,
    * destFile = NULL
  ;
  
  readFile = fopen(source, "rb"); 

  destFile = fopen(dest, "wb"); 
  
  if (readFile == NULL && destFile == NULL) {
    error |= ERR_DESTINATION_FILE;
    error |= ERR_SOURCE_FILE;
    error |= ERR_B64_DECODE;
  } else if (readFile == NULL) {
    error |= ERR_SOURCE_FILE;
    error |= ERR_B64_DECODE;
  } else if (destFile == NULL) {
    error |= ERR_DESTINATION_FILE;
    error |= ERR_B64_DECODE;
  } else {
  
    error = base64_decodeStream(readFile, destFile);

  }    
    
  if ( readFile != NULL && fclose(readFile) != 0 ) {
    error |= ERR_SOURCE_FILE;
    error |= ERR_B64_DECODE;
  }
  readFile = NULL;
  if ( destFile != NULL && fclose(destFile) != 0 ) {
    error |= ERR_DESTINATION_FILE;
    error |= ERR_B64_DECODE;
  }
  destFile = NULL;
  
  return error;
}

/**
 * Kodiert einen Stream mit Binaerdaten mit Base64 zu einem ASCII-Text.
 * 
 * @param FILE * source Quelldatei
 * @param FILE * dest Zieldatei
 * @pre source != NULL
 * @pre dest != NULL
 * @return ErrorSet mit moeglichen Fehlercodes:
 *  - ERR_B64_ENCODE Ein Fehler ist aufgetreten.
 *  - ERR_SOURCE_FILE Quelldatei nicht lesbar
 *  - ERR_DESTINATION_FILE Zieldatei nicht beschreibbar
 */
ErrorSet
base64_encodeStream(FILE * source, FILE * dest) {
  assert (source != NULL);
  assert (dest != NULL);
  
  ErrorSet
    error = ERR_NULL
  ;
  
  int 
    //Das einzulesende Zeichen
    read = '\0',
    //Kodiertes Zeichen
    encode = '\0',
    dummy = '=',
    buffersize = 0,
    revBuffer = 6
  ;

  unsigned int 
    mask6 = 63,  //0011 1111
    mask = 255  //1111 1111
  ;
  
 
  while (!error && (read = fgetc(source)) != EOF) {
    revBuffer = revBuffer - 2;
    buffersize = buffersize + 2;
    encode = (encode | (read >> buffersize)) & (mask6);
    if ( fputc(base64[encode], dest) != base64[encode] ) {
      error |= ERR_B64_ENCODE;
      error |= ERR_DESTINATION_FILE;
    } else {
      // 0011 0000       0000 0011
      encode = (read & ~(mask << buffersize)) << revBuffer;
    
      if (buffersize == 6 && revBuffer == 0) {
        buffersize = 0;
        revBuffer = 6;
        if ( fputc(base64[encode], dest) != base64[encode] ) {
          error |= ERR_B64_ENCODE;
          error |= ERR_DESTINATION_FILE;
        } else {
          encode = '\0';
        }
      }
    }
  }
  
  if (ferror(source) != 0) {
    error |= ERR_SOURCE_FILE;
    error |= ERR_B64_ENCODE;
  }
  
  if (!error && (buffersize > 0 || revBuffer < 6)) {
    buffersize = 6 - buffersize;
    if ( fputc(base64[encode], dest) != base64[encode] ) {
      error |= ERR_DESTINATION_FILE;
      error |= ERR_B64_ENCODE;
    }
    while (buffersize != 0) {
      if ( fputc((char)dummy, dest) != dummy ) {
        error |= ERR_DESTINATION_FILE;
        error |= ERR_B64_ENCODE;
      }
      buffersize = buffersize - 2;
    }
  }
  return error;
}

/**
 * Dekodiert einen Stream mit mit Base64 kodierten Daten zu einem
 * Stream mit Binaerdaten.
 * 
 * @param FILE * source Quelldatei
 * @param FILE * dest Zieldatei
 * @pre source != NULL
 * @pre dest != NULL
 * @return ErrorSet mit moeglichen Fehlercodes:
 *  - ERR_B64_DECODE Ein Fehler ist aufgetreten.
 *  - ERR_SOURCE_FILE Quelldatei nicht lesbar
 *  - ERR_DESTINATION_FILE Zieldatei nicht beschreibbar
 *  - ERR_INVALID_B64_DATA Ungueltiges Zeichen in der Quelldatei oder
 *    Fehlendes Zeichen in der Quelldatei (Anzahl der Zeichen % 4 != 0)
 */
ErrorSet
base64_decodeStream(FILE * source, FILE * dest) {
  assert (source != NULL);
  assert (dest != NULL);
  
  ErrorSet
    error = ERR_NULL
  ;
  
  unsigned char
    array[ 256 + 1 ] = {0}
  ;
  
  int 
    //Das einzulesende Zeichen
    read = '\0',
    //Kodiertes Zeichen
    decode = '\0',
    dummy = '=',
    buffersize = 6,
    revBuffer = 0
  ;
  
  long unsigned int
    count = 0;
  ;

  unsigned int
    mask8 = 255  //1111 1111
  ;
  
  while (count <= sizeof(base64)) {
    array[base64[count]] = count + 1;
    count++;
  }
  
  while (!error && (read = fgetc(source)) != EOF) {
    //Ueberpruefung auf Korrektheit des Zeichens
    if (array[read] == 0) {
      //Ueberpruefung auf EOF
      if ((char)read != (char)dummy){
        //Ungueltiges Zeichen in Quelldatei
        error |= ERR_INVALID_B64_DATA;
        error |= ERR_B64_DECODE;
        //Vorletztes Zeichen dummy und letztes Zeichen dummy
      } else if(buffersize == 2 && (read = fgetc(source)) == dummy) {
        //ueberpruefung ob das folgende Zeichen EOF ist
        if(feof(source) == 0) {
          //anzahl an Zeichen ist korrekt
          buffersize = 6;
        } else {
          error |= ERR_INVALID_B64_DATA;
          error |= ERR_B64_DECODE;
        }
      } else if(buffersize == 0 && feof(source) == 0) {
        buffersize = 6;
      } else {
        error |= ERR_INVALID_B64_DATA;  
        error |= ERR_B64_DECODE;  
      }
      
    //Zeichen ist in Base64 vertreten
    } else if (buffersize == 6) {
      //1. Zeichen der vierer Kette
      //1111 1100  <<  0011 1111
      buffersize = buffersize - 2;
      revBuffer = revBuffer + 2;
      decode = ((array[(int)read] - 1) << revBuffer) & mask8;
    
    } else {
  
      decode = (decode | ((array[(int)read] - 1) >> buffersize)) & mask8;
    
      if ( fputc((char) decode, dest) != decode ) {
        error |= ERR_DESTINATION_FILE;
        error |= ERR_B64_DECODE;
      } else {
    
        buffersize = buffersize - 2;
        revBuffer = revBuffer + 2;
        
        decode = ((array[(int)read] - 1) << revBuffer) & mask8;
        if(buffersize < 0) {
          buffersize = 6;
          revBuffer = 0;
        }
      }
    }
  }
  
  if (ferror(source)) {
    error |= ERR_SOURCE_FILE;
    error |= ERR_B64_DECODE;
  }
  
  if (!error && buffersize != 6) {
    error |= ERR_INVALID_B64_DATA;
    error |= ERR_B64_DECODE;
  }
  return error;
}
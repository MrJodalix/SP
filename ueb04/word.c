/**
 * Implementierung der Wort-Funktionen
 *
 * @author mhe, mre, tti, Joshua-Scott Schöttke, Ilana Schmara, Gruppe 21
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "word.h"
#include "error.h"

/** Referenzaehler fuer die gespeicherten Woerter */
int word_refs = 0;

/**
 * Kopiert die uebergebene Zeichenkette in einen neu reservierten
 * Speicherbereich. Der Speicherbereich wird durch word_copy reserviert.
 *
 * @param[in] str die zu kopierende Zeichenkette
 *
 * @return Zeiger auf das neue Wort
 *
 * @pre str != NULL
 */
Word
word_copy(char * str) {
  assert(str != NULL);
  
  Word copy = malloc( (strlen(str) + 1) * sizeof(char));
  word_refs++;
  
  if(copy == NULL) {
    error_print(stderr, ERR_OUT_OF_MEMORY);
    exit(ERR_OUT_OF_MEMORY);
  }
  
  strcpy(copy, str);
  
  //if( strcpy(copy, str) == NULL ) {
  //  error_print(stderr, ERR_OUT_OF_MEMORY);
  //  exit(ERR_OUT_OF_MEMORY);
  //}
  
  return copy;
}

/**
 * Gibt den vom Wort belegten Speicherbereich wieder frei.
 * Das uebergebene Wort darf danach nicht mehr verwendet werden.
 *
 * @param[in/out] w Wort
 *
 * @return NULL
 */
Word
word_delete(Word w) {
    
  if (w != NULL) {
    free(w);
    word_refs--;
    w = NULL;
  }
  
  return NULL;
}

/**
 * Implementierung der Liste von Wort-Vorkommen
 *
 * @author mhe, mre, tti, Joshua-Scott Schöttke, Ilana Schmara, Gruppe 21
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "occlist.h"
#include "error.h"

/** Referenzaehler fuer die gespeicherten OccList-Knoten */
int occlist_refs = 0;

/**
 * Erzeugt eine leere Liste.
 * Da eine Liste nur ein Zeiger auf ein Element ist, ist die leere Liste der
 * Nullzeiger.
 *
 * @return Leere Liste
 */
OccList
occlist_empty() {
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
occlist_isEmpty(OccList l) {
  return l == occlist_empty();
}

/**
 * Liefert das Kopf-Element der Liste.
 *
 * @param[in] l Liste
 *
 * @return Das erste Element
 *
 * @pre Die Liste darf nicht leer sein.
 */
Occurrence
occlist_head(OccList l) {
  assert(!occlist_isEmpty(l));
  
  return l->elements;
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
OccList
occlist_tail(OccList l) {
  assert(!occlist_isEmpty(l));
  
  return l->next;
}

/**
 * Fuegt das Element vorne an der Liste an und gibt einen Zeiger auf den neuen
 * Listenanfang zurueck.
 *
 * @param[in] l   Liste
 * @param     occ Element
 *
 * @return Veraenderte Liste
 */
OccList
occlist_cons(OccList l, Occurrence occ) {
    
  OccList result = malloc( sizeof(struct OccListNode) );
  occlist_refs++;
  
  if(result == NULL) {
    error_print(stderr, ERR_OUT_OF_MEMORY);
    exit(ERR_OUT_OF_MEMORY);
  }
  
  result->elements = occ;
  result->next = l;
  
  return result;
}

/**
 * Fuegt das Element sortiert in die Liste ein.
 * Dabei wird zunaechst aufsteigend nach line und, falls line identisch ist,
 * aufsteigend nach pos sortiert. Wenn die Occurence schon in der Liste
 * vorhanden ist, wird sie nicht erneut eingefuegt.
 *
 * @param[in] l   Liste
 * @param     occ Element
 *
 * @return Veraenderte Liste
 */
OccList
occlist_insert(OccList l, Occurrence occ) {
  //Iterierungsvariable
  OccList run = l;
  //Abbruchsvariable
  int inserted = 1;
  //Falls die Liste beim Eintritt leer ist, wird dies vorher in index_make abgefangen
  if(l == NULL){
    l = occlist_cons(l, occ);
  } else {
    while ( run != NULL && inserted != 0) {
      //ueberprueft auf das Ende der Liste
      if ( run->next == NULL ) {
        if ((run->elements.line < occ.line) 
            || (run->elements.line == occ.line && run->elements.pos < occ.pos )) {
          run->next = occlist_cons(run->next, occ);
          inserted = 0;
        } else {
          l = occlist_cons(l, occ);
          inserted = 0;
        }
      } else {
        // Einfuegen wenn die Line gleich ist, aber die Pos ungleich
        if ((( run->elements.line == occ.line )
            //ueberpruft ob occ zwischen zwei Elementen der Liste liegt
              && ( run->elements.pos < occ.pos && run->next->elements.pos > occ.pos ) 
              && ( run->elements.pos != occ.pos )) 
        // Einfuegen, wenn die die Line zwischen der jetzigen und naechsten Line liegt
            || ((run->elements.line < occ.line ) 
              && (run->next->elements.line > occ.line))) {
          run->next = occlist_cons(run->next, occ);
          inserted = 0;
        }
        run = run->next;
      }
    }
  }
  return l;
}

/**
 * Hilfsfunktion
 * Loescht das Kopfelement aus einer Liste und gibt den belegten Speicher wieder frei.
 *
 * @param[in] l Liste
 *
 * @return Liste um ein Element verringert
 *
 * @pre Liste darf nicht leer sein
 */
OccList 
deleteFirstOcc(OccList l) {
  assert( !occlist_isEmpty(l) );
  
  OccList res = occlist_tail(l);
  free( l );
  occlist_refs--;
  
  return res;
}
/**
 * Loescht die gesamte Liste und gibt ihren belegten Speicher wieder frei.
 * Die uebergebene Liste darf danach nicht mehr verwendet werden.
 *
 * @param[in] l Liste
 *
 * @return leere Liste
 */
OccList
occlist_delete(OccList l) {  

  while( l != NULL ) {
    l = deleteFirstOcc(l);
  } 
  
  return occlist_empty();
}



/**
 * @file ueb02.c
 *
 * Hauptprogramm.
 *
 * @author mhe, mre, tti, <TODO Eure Namen ergaenzen>
 */


#include <stdio.h>
#include <assert.h>
#include "cipher.h"
#include "error.h"


/**
 * Gibt die Hilfe auf dem uebergebenen Stream (stdout/stderr) aus.
 *
 * @param[in] stream Ausgabestrom
 *
 * @pre stream != NULL
 */
void
printUsage(FILE * stream) {

  assert (stream != NULL);

  fprintf(stream, "Usage:\n");
  fprintf(stream, "ueb02 -h\n\n");
  fprintf(stream, "  shows this help and exits.\n\n");
  fprintf(stream, "- or -\n\n");
  fprintf(stream, "ueb02 OPERATION [ARGUMENT] [OPERATION [ARGUMENT], ...]\n\n");
  fprintf(stream, "  Executes a number of (simple cryptographic) operations. The maximum text\n");
  fprintf(stream, "  size for plain / cipher text and key is %i. The allowed input characters\n", MAX_TEXT_LENGTH );
  fprintf(stream, "  range from \"%c\" to \"%c\".\n\n", SMALLEST_CHAR, BIGGEST_CHAR);
  fprintf(stream, "  OPERATION:\n");
  fprintf(stream, "    -t TEXT:  Sets the TEXT as new (plain/cipher) text.\n");
  fprintf(stream, "    -C ROT:   Sets the cipher algorithm to caesar.\n");
  fprintf(stream, "              ROT is the rotation (a positive integer).\n");
  fprintf(stream, "    -V KEY:   Sets the cipher algorithm to vigenere.\n");
  fprintf(stream, "              KEY is the nonempty passkey.\n");
  fprintf(stream, "    -e:       Encodes and replaces the current text using the current\n");
  fprintf(stream, "              cipher algorithm.\n");
  fprintf(stream, "    -d:       Decodes and replaces the current text using the current\n");
  fprintf(stream, "              cipher algorithm.\n");
  fprintf(stream, "    -i:       Writes the histogram corresponding to the current text to\n");
  fprintf(stream, "              stdout, followed by a line break.\n");
  fprintf(stream, "    -w:       Writes the current text to stdout, followed by a line break.\n");
}


/**
 * Hauptprogramm.
 *
 * Ueberprueft zunaechst die Eingaben auf gueltige Syntax und fuehrt
 * sofern kein Fehler aufgetreten ist die Operationen gemaess der
 * Usage aus.
 *
 * @param argc Anzahl der Programmargumente.
 * @param[in] argv Array mit den Programmargumenten.
 *
 * @return Fehlercode.
 */
int
main(int argc, char * argv[]) {

  ErrorCode
      error = ERR_NULL
    ;
  
  if(argc < 2){
    error = ERR_CALL_MISSING_ARGS
  }

  return error;
}

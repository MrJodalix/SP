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
  fprintf(stream, "  size for plain / cipherCode text and key is %i. The allowed input characters\n", MAX_TEXT_LENGTH );
  fprintf(stream, "  range from \"%c\" to \"%c\".\n\n", SMALLEST_CHAR, BIGGEST_CHAR);
  fprintf(stream, "  OPERATION:\n");
  fprintf(stream, "    -t TEXT:  Sets the TEXT as new (plain/cipherCode) text.\n");
  fprintf(stream, "    -C ROT:   Sets the cipherCode algorithm to caesar.\n");
  fprintf(stream, "              ROT is the rotation (a positive integer).\n");
  fprintf(stream, "    -V KEY:   Sets the cipherCode algorithm to vigenere.\n");
  fprintf(stream, "              KEY is the nonempty passkey.\n");
  fprintf(stream, "    -e:       Encodes and replaces the current text using the current\n");
  fprintf(stream, "              cipherCode algorithm.\n");
  fprintf(stream, "    -d:       Decodes and replaces the current text using the current\n");
  fprintf(stream, "              cipherCode algorithm.\n");
  fprintf(stream, "    -i:       Writes the histogram corresponding to the current text to\n");
  fprintf(stream, "              stdout, followed by a line break.\n");
  fprintf(stream, "    -w:       Writes the current text to stdout, followed by a line break.\n");
}



typedef
enum {
	NO_CIPHER = 0,
	CAESAR = 1,
	VIGENERE = 2
}Cipher;

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
	
	Text text = EMPTY_TEXT;
	
	char *readStr = "\0",
		 *Key = "\0";
	
	int	idx = 1,
		ROT = 0;
					
	char	OP = '\0',
			END = '\0';
			
	Cipher code = NO_CIPHER;
	
	if(argc < 2){
		error = ERR_CALL_MISSING_ARGS;
	} else {
		while((error == ERR_NULL) && (argv[idx] != NULL)){
			if(sscanf(argv[idx],"-%c%c", &OP, &END) != 1){
				error = ERR_UNKNOWN_OPERATION;
			} else {
				switch(OP){
					case 'h':
						if(argc == 2){
							printUsage(stdout);
						} else {
							error = ERR_UNKNOWN_OPERATION;
						}
					break;
					case 't':
						idx++;
						if(sscanf(argv[idx],"%s%c", readStr, &END) == 1){
							error = readText(text, readStr);
						} else {
							error = ERR_UNKNOWN_OPERATION;
						}
					break;
					case 'C':
						idx++;
						code = CAESAR;
						if(sscanf(argv[idx],"%d%c", &ROT, &END) != 1){
							error = ERR_UNKNOWN_OPERATION;
						}
					break;
					case 'V':
						idx++;
						code = VIGENERE;
						if(sscanf(argv[idx],"%s%c", Key, &END) != 1){
							error = ERR_UNKNOWN_OPERATION;
						}
					break;
					case 'e':
						if(code == NO_CIPHER){
							error = ERR_ENCODE_WITHOUT_CIPHER;
						} else if(code == CAESAR){
							caesarEncode(text,ROT);
						} else if(code == VIGENERE){
							vigenereEncode(text,Key);
						}
					break;
					case 'd':
						if(code == NO_CIPHER){
							error = ERR_ENCODE_WITHOUT_CIPHER;
						} else if(code == CAESAR){
							caesarDecode(text,ROT);
						} else if(code == VIGENERE){
							vigenereDecode(text,Key);
						}
					break;
					case 'i':
						printHistogram(stdout,text);
					break;
					case 'w':
						printText(stdout,text);
					break;
					default:
						error = ERR_UNKNOWN_OPERATION;
				}
			}
			idx++;
		}
	}
	return error;
}

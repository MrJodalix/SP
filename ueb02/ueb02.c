/**
 * @file ueb02.c
 *
 * Hauptprogramm.
 *
 * @author mhe, mre, tti, Ilana Schmara, Joshua-Scott Schoettke, Gruppe 21
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
	
	Text 
		text = EMPTY_TEXT,
		key = EMPTY_TEXT
	;
	
	int	
		idx = 1,
		rot = -1
	;

	char	
		op = '\0',
		end = '\0',
		readStr[MAX_TEXT_LENGTH+1] = EMPTY_TEXT
	;		

	Cipher 
		code = NO_CIPHER
	;
	
	if(argc < 2){
		error = ERR_CALL_MISSING_ARGS;
	} else {
		while((error == ERR_NULL) && (argv[idx] != NULL)){
			if(sscanf(argv[idx],"-%c%c", &op, &end) != 1){
				error = ERR_UNKNOWN_OPERATION;
			} else {
				switch(op){
					case 'h':
						if(argc == 2){
							printUsage(stdout);
						} else {
							error = ERR_UNKNOWN_OPERATION;
						}
					break;
					case 't':
						idx++;
						if(sscanf(argv[idx],"%[^\n]%c", readStr, &end) == 1){
							error = readText(text, readStr);
						} else {
						    text[0] = '\0';
						}
					break;
					case 'C':
						idx++;
						code = CAESAR;
						if(sscanf(argv[idx],"%d%c", &rot, &end) != 1){
							error = ERR_CAESAR_INVALID_ROTATION;
						}
					break;
					case 'V':
						idx++;
						code = VIGENERE;
						if(sscanf(argv[idx],"%[^\n]%c", readStr, &end) == 1){
							error = readText(key, readStr);
							if (error == ERR_NULL){	
								if(key[0] == '\0'){
									error = ERR_VIGENERE_EMPTY_KEY; 
								}
							} else if (error == ERR_TEXT_ILLEGAL_CHAR){
								error = ERR_VIGENERE_KEY_ILLEGAL_CHAR; 
							} else if (error == ERR_TEXT_TOO_LONG){
								error = ERR_VIGENERE_KEY_TOO_LONG; 
							}
						} else {
							error = ERR_VIGENERE_MISSING_KEY;
						}
					break;
					case 'e':
						switch(code){
							case NO_CIPHER:	error = ERR_ENCODE_WITHOUT_CIPHER; 
							break;
							case CAESAR:
								if(rot < 0) {
									error = ERR_CAESAR_MISSING_ROTATION;
								} else if (text[0] == '\0'){
									error = ERR_TEXT_MISSING_TEXT;
								} else {
									caesarEncode(text, rot);
								}
							break;
							case VIGENERE:
								if(key[0] == '\0') {
									error = ERR_VIGENERE_MISSING_KEY;
								} else if (text[0] == '\0'){
									error = ERR_TEXT_MISSING_TEXT;
								} else {
									vigenereEncode(text, key); 
								}	
							break;
						}
					break;
					case 'd':
						switch(code){
							case NO_CIPHER:	error = ERR_ENCODE_WITHOUT_CIPHER; 
							break;
							case CAESAR:
								if(rot < 0) {
									error = ERR_CAESAR_MISSING_ROTATION;
								} else if (text[0] == '\0'){
									error = ERR_TEXT_MISSING_TEXT;
								} else {
									caesarDecode(text, rot);
								}
							break;
							case VIGENERE:
								if(key[0] == '\0') {
									error = ERR_VIGENERE_MISSING_KEY;
								} else if (text[0] == '\0'){
									error = ERR_TEXT_MISSING_TEXT;
								} else {
									vigenereDecode(text, key); 
								}
							break;
						}
					break;
					case 'i':
						printHistogram(stdout, text);
					break;
					case 'w':
						printText(stdout, text);
					break;
					default:
						error = ERR_UNKNOWN_OPERATION;
				}
			}
			idx++;
			
		}
	}
	if(error != ERR_NULL){
		printError(stderr, error);
		printUsage(stderr);
	}
	return error;
}

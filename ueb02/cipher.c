/**
 * @file cipher.c
 *
 * Implementation des Moduls mit Verschluesselungsfunktionen.
 *
 * @author mhe, mre, tti, Ilana Schmara, Joshua-Scott Schoettke, Gruppe 21
 *
 */

#include <stdio.h>
#include <assert.h>
#include "cipher.h"

/**
 * Verschluesselt einen Text mit Caesar-Chiffre, dabei wird der uebergebene
 * Text veraendert.
 *
 * @param[in]  plain Klartext
 * @param[out] plain Kryptotext
 * @param      rot   Rotation
 *
 * @pre plain != NULL
 *
 */
void
caesarEncode(Text plain, unsigned int rot) {
	
	assert(plain != NULL);
	
	int 
		i = 0
	;
	
	while(plain[i] != '\0'){
		//Wenn das Zeichen + die modulo Berechnung groeszer als BIGGEST_CHAR ist,
		//muessen wir die Anzahl aller erlaubten Zeichen noch einmal abziehen
		if((plain[i]) + (rot % (BIGGEST_CHAR-SMALLEST_CHAR+1)) > BIGGEST_CHAR){
			
			plain[i] =	((plain[i]) + (rot % (BIGGEST_CHAR-SMALLEST_CHAR+1))) - 
						(BIGGEST_CHAR-SMALLEST_CHAR+1);
						
		} else {
			plain[i] = ((plain[i]) + (rot % (BIGGEST_CHAR-SMALLEST_CHAR+1)));
		}
		i++;
	}
}

/**
 * Entschluesselt einen Text mit Caesar-Chiffre, dabei wird der uebergebene
 * Text veraendert.
 *
 * @param[in]  plain Kryptotext
 * @param[out] plain Klartext
 * @param      rot Rotation
 *
 * @pre plain != NULL
 *
 */
void
caesarDecode(Text plain, unsigned int rot) {
	
	assert(plain != NULL);
	
	int 
		inversRot = (BIGGEST_CHAR-SMALLEST_CHAR+1) - rot % (BIGGEST_CHAR-SMALLEST_CHAR+1)
	;
	
	caesarEncode(plain, inversRot);
	
}

/**
 * Verschluesselt einen Text mit Vigenere-Chiffre, dabei wird der uebergebene
 * Text veraendert.
 *
 * @param[in]  plain Klartext
 * @param[out] plain Kryptotext
 * @param[in]  pass  Passwort
 *
 * @pre plain != NULL
 * @pre pass != NULL
 * @pre pass ist nicht leer
 *
 */
void
vigenereEncode(Text plain, Text pass) {
	
	assert((plain != NULL) && (pass != NULL) && (sizeof(*pass) != 0));
	
	int 
		i = 0,
		j = 0
	;
		
	while(plain[i] != '\0'){
		if(pass[j] == '\0'){
			j = 0;
		}
		
		plain[i] = (((plain[i]-SMALLEST_CHAR) + (pass[j]-SMALLEST_CHAR))
					% (BIGGEST_CHAR-SMALLEST_CHAR+1))+ SMALLEST_CHAR;

		i++;
		j++;
	}
}

/**
 * Entschluesselt einen Text mit Vigenere-Chiffre, dabei wird der uebergebene
 * Text veraendert.
 *
 * @param[in]  plain Kryptotext
 * @param[out] plain Klartext
 * @param[in]  pass  Passwort
 *
 * @pre plain != NULL
 * @pre pass != NULL
 * @pre pass ist nicht leer
 *
 */
void
vigenereDecode(Text plain, Text pass) {
	
	assert((plain != NULL) && (pass != NULL) && (sizeof(*pass) != 0));
	
	int 
		i = 0,
		j = 0,
		inversRot = 0
	;

	while(plain[i] != '\0'){
		if(pass[j] == '\0'){
			j = 0;
		}
		
		inversRot = ((plain[i]-SMALLEST_CHAR) - (pass[j] - SMALLEST_CHAR)) 
						+ (BIGGEST_CHAR-SMALLEST_CHAR+1);

		plain[i] = (inversRot % (BIGGEST_CHAR-SMALLEST_CHAR+1)) + SMALLEST_CHAR;

		i++;
		j++;
	}
}

/**
 * Liest einen Text ein.
 *
 * @param[out] text eingelesener Text
 * @param[in]  str  Eingabestring
 *
 * @pre text != NULL
 * @pre str != NULL
 *
 * @return Fehlercode:
 *         ERR_TEXT_ILLEGAL_CHAR wenn der einzulesende Text ungueltige Zeichen enthaelt
 *         ERR_TEXT_TOO_LONG wenn der Text laenger ist als der verfuegbare Platz
 */
ErrorCode
readText(Text text, char * str) {
	
	assert((text != NULL) && (str != NULL));
	
	ErrorCode 
		error = ERR_NULL
	;
	
	int 
		i = 0
	;

	while(error == ERR_NULL && str[i] != '\0'){
		if(i >= MAX_TEXT_LENGTH){
			error = ERR_TEXT_TOO_LONG;
		} else if (str[i] >= SMALLEST_CHAR && str[i] <= BIGGEST_CHAR){
			text[i] = str[i];
			i++;
		} else {
			error = ERR_TEXT_ILLEGAL_CHAR;
		}
	}
		
	text[i] = '\0';

	return error;
}

/**
 * Schreibt den uebergebenen Text auf den uebergebenen Ausgabestrom.
 *
 * @param[in] stream Ausgabestrom
 * @param[in] text   Text
 *
 * @pre stream != NULL
 * @pre text != NULL
 *
 */
void
printText(FILE * stream, Text text) {
	
	assert((text != NULL) && (stream != NULL));
	
	fprintf(stream,"%s\n", text);
}

/**
 * Gibt das Histogram des uebergebenen Texts auf dem uebergebenen Ausgabestrom aus.
 *
 * Die Ausgabe erfolgt spaltenweise in zwei Zeilen. Eine Spalte beinhaltet
 * stets das im Text vorhandene Zeichen (Auftrittshaeufigkeit > 0) und die
 * Anzahl seiner Vorkommen. Die Inhalte der Spalten sind voneinander durch
 * Leerzeichen getrennt und rechtsbuendig ausgerichtet. Die Breite der Anzahl
 * der Vorkommen bestimmt die Breite der Spalte. Die Zeichen werden gemaess
 * ihrer Reihenfolge im Zeichenvorrat ausgegeben.
 *
 * @param[in] stream Ausgabestrom
 * @param[in] text   Text
 *
 * @pre stream != NULL
 * @pre text != NULL
 *
 */
void
printHistogram (FILE * stream, Text text) {
	
	assert((text != NULL) && (stream != NULL));
	
	int 
		i = 0,
		width = 1,
		charCount[BIGGEST_CHAR-SMALLEST_CHAR+1] = {0}
	;

	
	while(text[i] != '\0'){
		charCount[text[i] - SMALLEST_CHAR]++;
		i++;
	}
	
	for (int k = 0; k < (BIGGEST_CHAR-SMALLEST_CHAR+1); k++) {
		if(charCount[k] != 0){
			//Berechnung der Breite zur Ausgabe
			if(charCount[k] < 10){
				width = 1;
			} else if(charCount[k] < 100){
				width = 2;
			} else if(charCount[k] < 1000){
				width = 3;
			}
			fprintf(stream, "%*c ", width, k + SMALLEST_CHAR);
		}
	}
	
	fprintf(stream, "\n");
	
	for (int k = 0; k < (BIGGEST_CHAR-SMALLEST_CHAR+1); k++) {
		if(charCount[k] != 0){
			fprintf(stream, "%d ", charCount[k]);
		}
	}
	
	fprintf(stream, "\n");
}


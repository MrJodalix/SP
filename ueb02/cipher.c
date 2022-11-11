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
  /** @TODO Implementation */
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
  /** @TODO Implementation */
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
  /** @TODO Implementation */
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
	assert((plain != NULL) && (pass != NULL) && (sizeof(*pass) >= 1));
  /** @TODO Implementation */
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
  /** @TODO Implementation */
	return ERR_NULL;
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
  /** @TODO Implementation */
}


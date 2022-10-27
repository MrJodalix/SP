/**
 * @file ueb01.c
 * Uebung Systemnahe Programmierung im WS 22/23.
 *
 * Ein einfaches Programm fuer Ganzzahlen, welches testen kann ob
 * eine Zahl prim oder froehlich ist und ausgehend von einer Zahl
 * deren Teiler finden kann.
 *
 * @author mhe, mre, tti, <TODO Hier tragt ihr eure Namen ein>
 *
 */

#include <stdio.h>


/**
 * Gibt die Hilfe auf dem uebergebenen Stream (stdout/stderr) aus.
 *
 * @param[in] stream Ausgabestrom
 */
void
printUsage  (FILE * stream) {
  fprintf(stream, "Usage:\n\n");
  
  fprintf(stream, "  ueb01 -h\n\n");
  
  fprintf(stream, "  shows this help and exits.\n\n");
  
  fprintf(stream, "  - or -\n\n");
  
  fprintf(stream, "  ueb01 NUM OP\n\n");
  
  fprintf(stream, "  checks whether a given number is prime or a happy number or finds the\n");
  fprintf(stream, "  divisors of a given number. A call always consists of a number followed\n");
  fprintf(stream, "  by an operation, where:\n\n");
  
  fprintf(stream, "  NUM has to be a positive integer number (including 0).\n\n");
  
  fprintf(stream, "  OP is one of:\n");
  fprintf(stream, "    p checks whether NUM is prime or not\n");
  fprintf(stream, "    d looks for the dividers of NUM\n");
  fprintf(stream, "    h checks whether NUM is a happy number\n");
  
}


/**
 * Funktion, die überprüft, ob die eingegebene Zahl eine Primzahl ist. Gibt 0 zurück, wenn sie eine ist und 1 wenn nicht.
 *
 * @param[in]  number Die zu überprüfende Zahl
 * @param[out] int    0 wenn sie eine Primzal ist, 1 wenn sie keine ist. 
 */
int isPrime (int number){
	int primNum = 0;
	int count = 2;

	if (number <= 1) {
	return primNum = 1;
	}
	
	if (number == 2) {
	return primNum;
	}
	
	if (number % 2 == 1){
		while ((primNum == 0) && ((count * count) <= number)) {
			if (number % count == 0) {
				primNum = 1;
			}
			count++;
		}
	} else {
		primNum = 1;
	}
	return primNum;
}

/**
 * Hauptprogramm.
 *
 * Ueberprueft zunaechst die Eingaben auf gueltige Syntax und fuehrt
 * sofern kein Fehler aufgetreten ist die dem angegebenen Operator 
 * entsprechende Berechnung aus:
 * 
 * d findet die Teiler einer Zahl und gibt sie aus
 * h ueberprueft, ob die angegebene Zahl froehlich ist
 * p prueft, ob die angegebene Zahl prim ist  
 *
 * Es wird entweder das Ergebnis der Berechnung ausgegeben oder eine 
 * entsprechende Fehlermeldung gefolgt von der Hilfe.
 *
 * @param[in] argc Anzahl der Programmargumente.
 * @param[in] argv Array mit den Programmargumenten.
 *
 * @return Fehlercode.
 */
int
main (int argc, char * argv[]) {
	Error err = ERR_None;
	char op = '\0', END = '\0';
	int next = 0;
	int previous = 0;
	int number = 0;

	switch(argc) {
		case 0:
		case 1: 		
			err = ERR_NoParameters;
		break;
		case 2:
			/* Prüfung auf die korrekte Eingabe des Hilfeaufrufs. */
			if(sscanf(argv[1], "-%c%c",  &OP, &END) && (OP == 'h') && (END == '\0'))){
				printUsage(stdout);
			} else {
				err = ERR_WrongHelp;
			}
		break;
		case 3:
			
		break;
		default:
	}
	return 0;
}

/** * @file ueb01.c
 * Uebung Systemnahe Programmierung im WS 22/23.
 *
 * Ein einfaches Programm fuer Ganzzahlen, welches testen kann ob
 * eine Zahl prim oder froehlich ist und ausgehend von einer Zahl
 * deren Teiler finden kann.
 *
 * @author mhe, mre, tti, Joshua-Scott Schöttke, Ilana Schmara, Gruppe 21
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

/*
typedef enum{
	ERR_None,
	ERR_NoParameters,
	ERR_WrongHelp,
	ERR_TooMuchInformation
}Error;
*/


/**
 * 
 *
 *
 */
int isDividable(int number){
	int count = 1;

	if(number % count == 0){

	}
}

/**
 * Funktion, die überprüft, ob die eingegebene Zahl eine Primzahl ist. 
 * Gibt 1 zurück, wenn sie eine ist und 0 wenn nicht.
 *
 * @param[in]  number Die zu überprüfende Zahl
 * @param[out] int    1 wenn sie eine Primzal ist, 0 wenn sie keine ist. 
 */
int isPrime (int number){
	int primNum = 1, //Erste Annahme eine Primzahl
	    count = 2;

	//Die Kleinste Primzahl ist 2
	if (number <= 1) {
		primNum = 0;
	} else {
		if (number == 2) {
			primNum = 1;
		} else {
			//Prüfung auf ungerade Zahlen	
			if (number % count == 1){
				count++;
				//Berechnung ob die Zahl teilbar durch das Quadrat von count ist
				while ((primNum == 1) && ((count * count) <= number)) {
					if (number % count == 0) {
						primNum = 0;
					}
					count += 2;
				}
			} else {
				primNum = 0;
			}
		}
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
	//Error err = ERR_None;
	char op = '\0', 
	     END = '\0';
	int next = 0, 
	    previous = 0, 
	    number = 0;

	switch(argc) {
		case 0:
		case 1: 		
		//	err = ERR_NoParameters;
		break;
		case 2:
			/* Prüfung auf die korrekte Eingabe des Hilfeaufrufs. */
			if(sscanf(argv[1], "-%c%c", &op, &END) && (op == 'h') && (END == '\0')){
				printUsage(stdout);
			} else {
				//err = ERR_WrongHelp;
				fprintf(stderr, "%s\n", "Falsche Hilfe ausgabe! Entferne mich bitte noch!!!");
			}
		break;
		case 3:
			if(sscanf(argv[1], "%i%c", &number, &END) == 1){
				if(sscanf(argv[2], "%c%c", &op, &END) == 1){
					if (number >= 0) {
						switch(op){
							case 'd':
                                                                if(isDividable(number)){
									fprintf(stdout, "%s%d%s\n", "The number ", number," has the following divisors: TEILER");
								} else {
									fprintf(stdout, "%s%d%s\n", "The number ", number," is not dividable.");
                                                                }
							break;
							case 'h':
                                                                if(isHappy(number)){
                                                                        fprintf(stdout, "%s%d%s\n", "*\\o/* The number ", number, " is a happy number. *\\o/*");
                                                                } else {
                                                                        fprintf(stdout, "%s%d%s\n", "O_o The number ", number," is a sad number. o_O");
                                                                }

							break;
							case 'p':
								if(isPrime(number)){
                		                                        fprintf(stdout, "%s%d%s\n", "*\\o/* The number ", number, " is a prime number. *\\o/*");
                                		                } else {
                                               		 	        fprintf(stdout, "%s%d%s\n", "O_o The number ", number," is not a prime number. o_O");
                                                		}
							break;
							default:
								fprintf(stderr, "%s\n", "Falscher Operator!");
						}
					} else {
						fprintf(stderr, "%s\n", "Zahl muss Null oder positiv sein!");
					}
				} else {
					fprintf(stderr,"%s\n", "Zu viele Zeichen für einen Operator!");
				}		
			} else {
				fprintf(stderr,"%s\n", "Positive Ganzzahl nicht erkannt!");
			}
		break;
		default:
			//err = ERR_TooMuchInformation;
	}
	return 0;
}

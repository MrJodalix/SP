/** * @file ueb01.c
 * Uebung Systemnahe Programmierung im WS 22/23.
 *
 * Ein einfaches Programm fuer Ganzzahlen, welches testen kann ob
 * eine Zahl prim oder froehlich ist und ausgehend von einer Zahl
 * deren Teiler finden kann.
 *
 * @author mhe, mre, tti, Joshua-Scott Schoettke, Ilana Schmara, Gruppe 21
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
 * aufteilung der verschiedenen Fehlercodes
 * ERR_None ist mit 0 initialisiert
 */
typedef enum{
	//Kein Fehlerfall
	ERR_None = 0,
	//Keine Parameter oder nur der Programmname wurden angegeben
	ERR_NoParameters = 1,
	//Falscher Hilfeaufruf. Bsp: -hx oder -x
	ERR_WrongHelp = 2,
	//Falsches Format für Zahlen
	ERR_WrongNumber = 3,
	//Falsches Format für Operatoren
	ERR_WrongOperatorFormat = 4,
	//Wenn die Zahl negativ ist
	ERR_NoPositivNumber = 5,
	//Ein nicht implementierter Operator
	ERR_WrongOperator = 6,
	//Zu viele Parameter
	ERR_TooMuchInformation = 7
}Error;

/**
 * Gibt im Fehlerfall eine eindeutige Fehlermeldung, sowie die Hilfe auf stderr aus.
 * 
 * @param[in] err	Fehlercode 
 * @param[out] err	EXIT_Code
 */
Error
errorHandling(Error err){
	switch(err) {
		case ERR_None:
		break;
		case ERR_NoParameters: fprintf(stderr, "%s\n", "Error: No parameters!");
		break;
		case ERR_WrongHelp: fprintf(stderr, "%s\n", "Error: Wrong help call!");
		break;
		case ERR_WrongNumber: fprintf(stderr, "%s\n", "Error: NUM must be integer!");
		break;
		case ERR_WrongOperatorFormat: fprintf(stderr, "%s\n", "Error: Wrong format for OP!");
		break;
		case ERR_NoPositivNumber: fprintf(stderr, "%s\n", "Error: NUM must be positive!");
		break;
		case ERR_WrongOperator: fprintf(stderr, "%s\n", "Error: Wrong OP!");
		break;
		case ERR_TooMuchInformation: fprintf(stderr, "%s\n", "Error: Too much information!");
		break;
	}
	if (err != ERR_None) {
		printUsage(stderr);
	}
	return err;
}


/**
 * Funktion, die ueberprueft, ob die eingegebene Zahl eine froehliche Zahl ist. 
 * Gibt 1 zurueck, wenn sie eine ist und 0 wenn nicht.
 *
 * @param[in]  number Die zu ueberpruefende Zahl
 * @param[out] int    1 wenn sie eine froehliche Zahl ist, 0 wenn sie keine ist. 
 */
int 
isHappy(int number){
	int position = 1,	//position der Ziffer die quadriert werden soll
		temp = 0,		//zwischenspeicherung
		copyNum = number,
		sum = 0;		//Ergebnis jeder Einzelberechnung und Endergebnis

	//Die Null ist keine froehliche Zahl
	if(number != 0){
		while(sum != 1 && sum != 4){
			sum = 0;
			//Einzelne Positions- und Teilsummenberechnung
			while (position <= copyNum){
				//Bestimmung der zu betrachtenden Ziffer in der Zahl
				temp = (copyNum % (position * 10));
				//Restbetrag ist die zu untersuchende Ziffer
				temp = temp / position;
				sum = sum + (temp * temp);
				position = position * 10;
			}
			position = 1;
			copyNum = sum;
		}
		if (sum == 4) {
			sum = 0;
		}
	}
	return sum;
}

/**
 * Funktion, die ueberprueft, ob die eingegebene Zahl eine Primzahl ist. 
 * Gibt 1 zurueck, wenn sie eine ist und 0 wenn nicht.
 *
 * @param[in]  number Die zu ueberpruefende Zahl
 * @param[out] int    1 wenn sie eine Primzal ist, 0 wenn sie keine ist. 
 */
int 
isPrime (int number){
	int primNum = 1, //Erste Annahme eine Primzahl
		count = 2;
	
	//Die Kleinste Primzahl ist 2
	if (number <= 1) {
		primNum = 0;
	} else if (number == 2) {
		primNum = 1;
	//Pruefung auf ungerade Zahlen
	} else if (number % count == 1){
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
	char op = '\0', 
		 END = '\0';
	int divisor = 2,
		smallestDiv = 2,
		number = 0;

	switch(argc) {
		case 0:
		case 1: 		
			err = ERR_NoParameters;
		break;
		case 2:
			/* Pruefung auf die korrekte Eingabe des Hilfeaufrufs. */
			if(sscanf(argv[1], "-%c%c", &op, &END) == 1 && (op == 'h')){
				printUsage(stdout);
			} else {
				err = ERR_WrongHelp;
			}
		break;
		case 3:
			if(sscanf(argv[1], "%i%c", &number, &END) != 1){
				err = ERR_WrongNumber;
			} else if(sscanf(argv[2], "%c%c", &op, &END) != 1){
				err = ERR_WrongOperatorFormat;
			} else if (number < 0) {
				err = ERR_NoPositivNumber;
			} else {
				switch(op){
					case 'd':
						// Pruefung auf Teilbarkeit. Jede Zahl außer 0 hat Teiler. 
						// Mind. 1 und sich selbst
						if(number == 0){
							fprintf(stdout, "%s%d%s\n", "The number ", number,
											" is not dividable.");
						} else if(number == 1){
							fprintf(stdout, "%s%d%s%d\n", "The number ", number,
											" has the following divisors: ",number);
						} else {
							fprintf(stdout, "%s%d%s", "The number ", number,
											" has the following divisors: 1, ");
							// Wenn die Zahl eine Primzahl ist, brauchen wir nur 
							// 1 und die Zahl selber ausgeben
							if(!isPrime(number)){
								//divisor = 2 zu anfang
								while((divisor * divisor) <= number){
									if(number % divisor == 0){
										fprintf(stdout, "%d, ",divisor);
										smallestDiv = divisor;
									}
									divisor++;
								}
								//um Dopplung bei ungerader Anzahl an Divisoren zu vermeiden
								if((smallestDiv * smallestDiv) == number){
									smallestDiv--;
								}
								while(smallestDiv >= 2){
									if(number % smallestDiv == 0){
										fprintf(stdout, "%d, ", (number/smallestDiv));
									}
									smallestDiv--;
								}
							}
							fprintf(stdout, "%d\n",number);
						}
					break;
					case 'h':
						if(!isHappy(number)){
							fprintf(stdout, "%s%d%s\n", "O_o The number ", number,
											" is a sad number. o_O");
						} else {
							fprintf(stdout, "%s%d%s\n", "*\\o/* The number ", number, 
											" is a happy number. *\\o/*");
						}
					break;
					case 'p':
						if(!isPrime(number)){
							fprintf(stdout, "%s%d%s\n", "O_o The number ", number,
											" is not a prime number. o_O");
						} else {
							fprintf(stdout, "%s%d%s\n", "*\\o/* The number ", number, 
											" is a prime number. *\\o/*");
						}
					break;
					default:
						err = ERR_WrongOperator;
				}
			}
		break;
		default:
			err = ERR_TooMuchInformation;
	}
	return errorHandling(err);
}

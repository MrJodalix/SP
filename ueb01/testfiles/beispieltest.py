#!/usr/bin/env python

suite = [
    Test (
        name = "Hilfeaufruf",
        description = "Vergleich mit der Textdatei usage.txt",
        command = "$DUT -h",
        stdout = "",
        stderr = ExpectFile("usage.txt"),
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Einfacher Primzahltest mit Primzahl",
        description = "Ist 7 eine Primzahl?",
        command = "$DUT 7 p",
        stdout = "*\o/* The number 7 is a prime number. *\o/*$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Primzahltest mit Primzahl (Variante 2)",
        description = "Ist 7 eine Primzahl?",
        command = "$DUT 7 p",
        stdout = ExpectFile("seven_prime.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Test auf froehliche Zahl nicht erfolgreich",
        description = "4 h",
        command = "$DUT 4 h",
        stdout = "O_o The number 4 is a sad number. o_O$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Teiler einer nicht-Primzahl",
        description = "51 d",
        command = "$DUT 51 d",
        stdout = "The number 51 has the following divisors: 1, 3, 17, 51$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Fehlerfall: keine Parameter",
        description = "Fehlermeldung muss mit 'Error:' beginnen und auf stderr stehen, Exitcode ungleich 0",
        command = "$DUT",
        stdout = "",
        stderr = "regex:^Error:",
        returnCode = lambda v: v !=0,
        timeout = 10
    ),
]

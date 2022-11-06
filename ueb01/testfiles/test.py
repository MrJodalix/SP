#!/usr/bin/env python

suite = [
    Test (
        name = "Hilfeausgabe mit zu vielen Parametern",
        description = "Erwartet die passende Fehlermeldung auf stderr.",
        command = "$DUT -h p",
        stdout = "",
        stderr = "$Error: Number must be integer!",
        returnCode = 3,
        timeout = 10
    ),
    
    Test (
        name = "Programmaufruf mit einem falschen Parameter",
        description = "Erwartet die passende Fehlermeldung auf stderr.",
        command = "$DUT p",
        stdout = "",
        stderr = "$Error: Wrong help call!",
        returnCode = 2,
        timeout = 10
    ),
    Test (
        name = "Programmaufruf mit zu vielen Parametern",
        description = "Erwartet die passende Fehlermeldung auf stderr.",
        command = "$DUT p d f",
        stdout = "",
        stderr = "$Error: Too much information!",
        returnCode = 7,
        timeout = 10
    ),
    Test (
        name = "1. Programmaufruf mit leerem String",
        description = "Erwartet die passende Fehlermeldung auf stderr.",
        command = "$DUT \"\" d",
        stdout = "",
        stderr = "$Error: Number must be integer!",
        returnCode = 3,
        timeout = 10
    ),
    Test (
        name = "2. Programmaufruf mit leerem String",
        description = "Erwartet die passende Fehlermeldung auf stderr.",
        command = "$DUT \"\" \"\"",
        stdout = "",
        stderr = "$Error: Number must be integer!",
        returnCode = 3,
        timeout = 10
    ),
    Test (
        name = "3. Programmaufruf mit leerem String",
        description = "Erwartet die passende Fehlermeldung auf stderr.",
        command = "$DUT 5 \"\"",
        stdout = "",
        stderr = "$Error: Wrong format for operator!",
        returnCode = 4,
        timeout = 10
    ),
    Test (
        name = "4. Programmaufruf mit leerem String",
        description = "Erwartet die passende Fehlermeldung auf stderr.",
        command = "$DUT \"\" \"\" \"\"",
        stdout = "",
        stderr = "$Error: Too much information!",
        returnCode = 7,
        timeout = 10
    ),
    Test (
        name = "5. Programmaufruf mit leerem String",
        description = "Erwartet die passende Fehlermeldung auf stderr.",
        command = "$DUT \"\"",
        stdout = "",
        stderr = "$Error: Wrong help call!",
        returnCode = 2,
        timeout = 10
    ),
    Test (
        name = "Programmaufruf falschem Operator",
        description = "Erwartet die passende Fehlermeldung auf stderr.",
        command = "$DUT 5 z",
        stdout = "",
        stderr = "$Error: Wrong Operator!",
        returnCode = 6,
        timeout = 10
    ),
    
    Test (
        name = "Primzahltest mit 0",
        description = "Ist 0 eine Primzahl?",
        command = "$DUT 0 p",
        stdout = "O_o The number 0 is not a prime number. o_O$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Primzahltest mit 1",
        description = "Ist 1 eine Primzahl?",
        command = "$DUT 1 p",
        stdout = "O_o The number 1 is not a prime number. o_O$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Primzahltest mit 2",
        description = "Ist 2 eine Primzahl?",
        command = "$DUT 2 p",
        stdout = "O_o The number 2 is not a prime number. o_O$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Primzahltest mit 3",
        description = "Ist 3 eine Primzahl?",
        command = "$DUT 3 p",
        stdout = "*\o/* The number 3 is a prime number. *\o/*$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Primzahltest mit Oktalzahl 0771",
        description = "Ist 0771 eine Primzahl?",
        command = "$DUT 0771 p",
        stdout = "O_o The number 505 is not a prime number. o_O$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Primzahltest mit Oktalzahl 053",
        description = "Ist 053 eine Primzahl?",
        command = "$DUT 053 p",
        stdout = "*\o/* The number 43 is a prime number. *\o/*$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Primzahltest mit Hexadezimalzahl 0x771",
        description = "Ist 0x771 eine Primzahl?",
        command = "$DUT 0x771 p",
        stdout = "O_o The number 1905 is not a prime number. o_O$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Primzahltest mit Hexadezimalzahl 0x2B",
        description = "Ist 0x2B eine Primzahl?",
        command = "$DUT 0x2B p",
        stdout = "*\o/* The number 43 is a prime number. *\o/*$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Primzahltest mit -1",
        description = "Fehlerfall bei -1 beim Primzahltest",
        command = "$DUT -1 p",
        stdout = "",
        stderr = "$Error: Number must be positive!",
        returnCode = "5",
        timeout = 10
    ),
    
    Test (
        name = "Froehliche Zahl Test mit 0",
        description = "Ist 0 eine froehliche Zahl?",
        command = "$DUT 0 h",
        stdout = "O_o The number 0 is a sad number. o_O$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Froehliche Zahl Test mit 1",
        description = "Ist 1 eine froehliche Zahl?",
        command = "$DUT 1 h",
        stdout = "*\o/* The number 1 is a happy number. *\o/*$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Froehliche Zahl Test mit 2",
        description = "Ist 2 eine froehliche Zahl?",
        command = "$DUT 2 h",
        stdout = "O_o The number 2 is a sad number. o_O$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Froehliche Zahl Test mit 998",
        description = "Ist 998 eine froehliche Zahl?",
        command = "$DUT 998 h",
        stdout = "*\o/* The number 998 is a happy number. *\o/*$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Froehliche Zahl Test mit Oktalzahl 01746",
        description = "Ist 01746 eine froehliche Zahl?",
        command = "$DUT 01746 h",
        stdout = "*\o/* The number 998 is a happy number. *\o/*$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Froehliche Zahl Test mit Hexadezimalzahl 0x3E6",
        description = "Ist 0x3E6 eine froehliche Zahl?",
        command = "$DUT 0x3E6 h",
        stdout = "*\o/* The number 998 is a happy number. *\o/*$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Froehliche Zahlen Test mit -1",
        description = "Fehlerfall bei -1 beim Test auf froehliche Zahlen",
        command = "$DUT -1 h",
        stdout = "",
        stderr = "$Error: Number must be positive!",
        returnCode = "5",
        timeout = 10
    ),
    
    Test (
        name = "Teiler einer Primzahl",
        description = "Teiler von 43 ausgeben",
        command = "$DUT 43 d",
        stdout = "The number 43 has the following divisors: 1, 43$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Teiler von 144",
        description = "Teiler von 144 ausgeben",
        command = "$DUT 144 d",
        stdout = "The number 144 has the following divisors: 1, 2, 3, 4, 6, 8, 9, 12, 16, 18, 24, 36, 48, 72, 144$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Teiler von 0",
        description = "Teiler von 0 ausgeben",
        command = "$DUT 0 d",
        stdout = "The number 0 is not dividable.$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Teiler von Oktalzahl 01746",
        description = "Teiler von 01746 ausgeben",
        command = "$DUT 01746 d",
        stdout = "The number 998 has the following divisors: 1, 2, 499, 998$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Teiler von Hexadezimalzahl 0x3E6",
        description = "Teiler von 0x3E6 ausgeben",
        command = "$DUT 0x3E6 d",
        stdout = "The number 998 has the following divisors: 1, 2, 499, 998$n",
        stderr = "",
        returnCode = "0",
        timeout = 10
    ),
    Test (
        name = "Teiler von -1",
        description = "Fehlerfall bei negativen Zahlen",
        command = "$DUT -1 d",
        stdout = "",
        stderr = "$Error: Number must be positive!",
        returnCode = "5",
        timeout = 10
    ),
]

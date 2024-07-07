#!/usr/bin/env python

suite = [
    Test (
        name = "Test auf ungueltiges Zeichen",
        description = "-t Zeichen auszerhalb des Zeichensatzes",
        command = "$DUT -t }",
        stdout = "",
        stderr = "regex:^Error: Illegal character in given text.",
        returnCode = 4,
        timeout = 10
        ),
    Test (
        name = "Test auf ungueltiges Zeichen",
        description = "-t zu viele Zeichen in Zeichensatz A-Z von 40 char werten",
        command = "$DUT -t ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ",
        stdout = "",
        stderr = "regex:^Error: Given Text too long.",
        returnCode = 5,
        timeout = 10
        ),
    Test (
        name = "Test auf 40 MAX Zeichen",
        description = "-t 40 Zeichen in Zeichensatz A-Z von 40 char werten",
        command = "$DUT -t ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMN -w",
        stdout = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMN",
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
    Test (
        name = "Test auf Zeichen nach dem Zeichensatz falsch",
        description = "-t [",
        command = "$DUT -t [CDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMN",
        stdout = "",
        stderr = "regex:^Error: Illegal character in given text.",
        returnCode = 4,
        timeout = 10
        ),
    Test (
        name = "1: Tests aus dem Foliensatz",
        description = "-t HALLO -C 1 -e",
        command = "$DUT -t HALLO -C 1 -e -w",
        stdout = "IBMMP",
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
    Test (
        name = "2: Tests aus dem Foliensatz",
        description = "-t ZOO -C 1 -e",
        command = "$DUT -t ZOO -C 1 -e -w",
        stdout = "APP",
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
    Test (
        name = "3: Tests aus dem Foliensatz",
        description = "-t HALLO -C 28 -e",
        command = "$DUT -t HALLO -C 28 -e -w",
        stdout = "JCNNQ",
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
    Test (
        name = "Test auf ungueltiges Zeichen",
        description = "-V Zeichen auszerhalb des Zeichensatzes",
        command = "$DUT -V }",
        stdout = "",
        stderr = "regex:^Error: Missing, empty or invalid key for vigenere cipher.",
        returnCode = 13,
        timeout = 10
        ),
        
    Test (
        name = "4: Tests aus dem Foliensatz",
        description = "-t HALLO -V ABCDE -e",
        command = "$DUT -t HALLO -V ABCDE -e -w",
        stdout = "HBNOS",
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
    
]



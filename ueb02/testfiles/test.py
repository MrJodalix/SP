#!/usr/bin/env python

suite = [
    Test (
        name = "Zu viel Text",
        description = "-t zu viele Zeichen eingegeben",
        command = "$DUT -t 0123456789012345678901234567890",
        stdout = "",
        stderr = "regex:^Error: Given Text too long.",
        returnCode = 5,
        timeout = 10
        ),
    Test (
        name = "Verschluesselung ohne -C oder -V",
        description = "-t HALLO -e",
        command = "$DUT -t HALLO -e",
        stdout = "",
        stderr = "regex:^Error: No cipher algorithm selected.",
        returnCode = 6,
        timeout = 10
        ),
    Test (
        name = "Entschluesselung ohne -C oder -V",
        description = "-t HALLO -d",
        command = "$DUT -t HALLO -d",
        stdout = "",
        stderr = "regex:^Error: No cipher algorithm selected.",
        returnCode = 7,
        timeout = 10
        ),

    Test (
        name = "Caesar Rotation setzen",
        description = "-C 6 ohne -t",
        command = "$DUT -C 6",
        stdout = ExpectFile("expected/empty.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
    Test (
        name = "Caesar mit Text als leerer String",
        description = "-t \"\" -C 8 -w",
        command = "$DUT -t \"\" -C 8 -w",
        stdout = ExpectFile("expected/empty_text.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
    Test (
        name = "Caesar ungueltige Rotation",
        description = "-C r",
        command = "$DUT -C r",
        stdout = "",
        stderr = "regex:^Error: Missing or invalid rotation for caesar cipher.",
        returnCode = 9,
        timeout = 10
        ),
    Test (
        name = "Caesar leere Rotation",
        description = "-C mit leerem String",
        command = "$DUT -C \"\"",
        stdout = "",
        stderr = "regex:^Error: Missing or invalid rotation for caesar cipher.",
        returnCode = 9,
        timeout = 10
        ),
    Test (
        name = "Caesar Rotation negative Zahl",
        description = "-C -1",
        command = "$DUT -C -1",
        stdout = "",
        stderr = "regex:^Error: Missing or invalid rotation for caesar cipher.",
        returnCode = 9,
        timeout = 10
        ),
    Test (
        name = "Caesar Encode ohne Text",
        description = "-C 8 -e",
        command = "$DUT -C 8 -e",
        stdout = ExpectFile("expected/empty.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
    Test (
        name = "Caesar Decode ohne Text",
        description = "-C 8 -d",
        command = "$DUT -C 8 -d",
        stdout = ExpectFile("expected/empty.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
    Test (
        name = "Caesar Decode ohne Schluessel",
        description = "-t Hallo -C -d",
        command = "$DUT -t Hallo -C -d",
        stdout = "",
        stderr = "regex:^Error: Missing or invalid rotation for caesar cipher.",
        returnCode = 9,
        timeout = 10
        ),
    Test (
        name = "Caesar Decode ohne Schluessel",
        description = "-t Hallo -C -d",
        command = "$DUT -t Hallo -C -d",
        stdout = "",
        stderr = "regex:^Error: Missing or invalid rotation for caesar cipher.",
        returnCode = 9,
        timeout = 10
        ),
    Test (
        name = "Caesar Encode und Decode",
        description = "-t Hallo -C 192 -w -e -w -d -w",
        command = "$DUT -t Hallo -C 192 -w -e -w -d -w",
        stdout = ExpectFile("expected/caesar_en_dec.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
    Test (
        name = "Caesar Encode und Decode mit 0",
        description = "-t Hallo -C 0 -w -e -w -d -w",
        command = "$DUT -t Hallo -C 0 -w -e -w -d -w",
        stdout = ExpectFile("expected/caesar_en_dec_0.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
        
    Test (
        name = "Vignenere Key setzen",
        description = "-V KEY ohne -t",
        command = "$DUT -V KEY",
        stdout =  ExpectFile("expected/empty.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
    Test (
        name = "Vignenere mit Text als leerer String",
        description = "-t \"\" -V KEY -w",
        command = "$DUT -t \"\" -V KEY -w",
        stdout = ExpectFile("expected/empty_text.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
    Test (
        name = "Vignenere Encode und Decode",
        description = "-t Hallo -V xyz -w -e -w -d -w",
        command = "$DUT -t Hallo -V xyz -w -e -w -d -w",
        stdout = ExpectFile("expected/vig_en_dec.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
    Test (
        name = "Vignenere Schluessel zu lang",
        description = "-V hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh",
        command = "$DUT -V hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh",
        stdout = "",
        stderr = "regex:^Error: Missing, empty or invalid key for vigenere cipher.",
        returnCode = 12,
        timeout = 10
        ),
    Test (
        name = "Vignenere leerer Schluessel",
        description = "-V mit leerem String",
        command = "$DUT -V \"\"",
        stdout = "",
        stderr = "regex:^Error: Missing, empty or invalid key for vigenere cipher.",
        returnCode = 11,
        timeout = 10
        ),
    Test (
        name = "Vignenere ohne Schluessel",
        description = "-t Hallo -V",
        command = "$DUT -t Hallo -V",
        stdout = "",
        stderr = "regex:^Error: Missing, empty or invalid key for vigenere cipher.",
        returnCode = 10,
        timeout = 10
        ),
        Test (
        name = "Vignenere Encode ohne Text",
        description = "-V KEY -e",
        command = "$DUT -V KEY -e",
        stdout = ExpectFile("expected/empty.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
    Test (
        name = "Vignenere Decode ohne Text",
        description = "-V KEY -d",
        command = "$DUT -V KEY -d",
        stdout = ExpectFile("expected/empty.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
        
    Test (
        name = "Histogramm, danach falsche Operation",
        description = "-i \"\"",
        command = "$DUT -i \"\"",
        stdout = ExpectFile("expected/empty_hist.txt"),
        stderr = "regex:^Error: Unknown Operation.",
        returnCode = 2,
        timeout = 10
        ),
    Test (
        name = "Histogramm mit Smallest Char und Biggest Char",
        description = "-t \"~~~~~~~----3333999~    \" -w -i",
        command = "$DUT -t \"~~~~~~~----3333999~    \" -w -i",
        stdout = ExpectFile("expected/hist.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
        ),
        

]



#!/usr/bin/env python

suite = [
    Test (
        name = "Beispiel aus der Aufgabenstellung",
        description = "Ausgabe leerer Text",
        command = "$DUT -w",
        stdout = ExpectFile("expected/empty_text.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel aus der Aufgabenstellung",
        description = "Ausgabe des Histograms des leeren Texts",
        command = "$DUT -i",
        stdout = ExpectFile("expected/empty_hist.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel aus der Aufgabenstellung",
        description = "Caesar ver- und entschluesseln",
        command = "$DUT -t \"Hallo Welt\" -C 12 -w -e -w -d -w",
        stdout = ExpectFile("expected/b_caesar.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel aus der Aufgabenstellung",
        description = "Vigenere ver- und entschluesseln",
        command = "$DUT -t \"Hallo Welt\" -w -V \"  XY \" -e -w -d -w",
        stdout = ExpectFile("expected/b_vigenere.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel aus der Aufgabenstellung",
        description = "Histogrammausgabe",
        command = "$DUT -t \"HAAAAAAAAAAAAAAALLO_WELT!\" -i",
        stdout = ExpectFile("expected/b_histogram.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel aus der Aufgabenstellung",
        description = "Komplexer Aufruf",
        command = "$DUT -C 5 -t \"HALLO\" -w -i -e -w -i -t \"Welt\" -w -e -w",
        stdout = ExpectFile("expected/b_complex_call.txt"),
        stderr = "",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Fehlerfall: keine Parameter",
        description = "Fehlermeldung und Errorcode muessen zu den Vorgaben passen.",
        command = "$DUT",
        stdout = "",
        stderr = "regex:^Error: No arguments given.",
        returnCode = 1,
        timeout = 10
    ),
]

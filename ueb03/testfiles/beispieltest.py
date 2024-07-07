#!/usr/bin/env python

suite = [
    Test (
        name = "Beispiel: encode 70 72 87",
        description = "=> 'RkhX' (3 Bytes -> 4 Bytes)",
        command = "$DUT -e expected/FHW.plain FHW.b64 && diff --binary FHW.b64 expected/FHW.b64",
        returnCode = 0,
        timeout = 10
    ),    
    Test (
        name = "Beispiel: encode 70 72",
        description = "=> 'Rkg=' (2 Bytes -> 3 Bytes + '=')",
        command = "$DUT -e expected/FH.plain FH.b64 && diff --binary FH.b64 expected/FH.b64",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: encode 70",
        description = "=> 'Rg==' (1 Byte -> 2 Bytes + '==')",
        command = "$DUT -e expected/F.plain F.b64 && diff --binary F.b64 expected/F.b64",
        returnCode = 0,
        timeout = 10
    ),
    
    Test (
        name = "Beispiel: decode 'RkhX'",
        description = "=> 70 72 87 (4 Bytes -> 3 Bytes)",
        command = "$DUT -d expected/FHW.b64 FHW.plain && diff --binary FHW.plain expected/FHW.plain",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: decode 'RKg='",
        description = "=> 70 72 (3 Bytes + '=' -> 2 Bytes)",
        command = "$DUT -d expected/FH.b64 FH.plain && diff --binary FH.plain expected/FH.plain",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: decode 'Rg=='",
        description = "=> 70 (2 Bytes + '==' -> 1 Byte)",
        command = "$DUT -d expected/F.b64 F.plain && diff --binary F.plain expected/F.plain",
        returnCode = 0,
        timeout = 10
    ),
    
    Test (
        name = "Beispiel: encode 'FH Wedel!'",
        description = "=> 'RkggV2VkZWwh'",
        command = "$DUT -e expected/FH_Wedel_.plain FH_Wedel_.b64 && diff --binary FH_Wedel_.b64 expected/FH_Wedel_.b64",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: encode 'FH Wedel'",
        description = "=> 'RkggV2VkZWw='",
        command = "$DUT -e expected/FH_Wedel.plain FH_Wedel.b64 && diff --binary FH_Wedel.b64 expected/FH_Wedel.b64",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: encode 'FH Wede'",
        description = "=> 'RkggV2VkZQ=='",
        command = "$DUT -e expected/FH_Wede.plain FH_Wede.b64 && diff --binary FH_Wede.b64 expected/FH_Wede.b64",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: encode 'FH Wed'",
        description = "=> 'RkggV2Vk'",
        command = "$DUT -e expected/FH_Wed.plain FH_Wed.b64 && diff --binary FH_Wed.b64 expected/FH_Wed.b64",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: encode 'FH We'",
        description = "=> 'RkggV2U='",
        command = "$DUT -e expected/FH_We.plain FH_We.b64 && diff --binary FH_We.b64 expected/FH_We.b64",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: encode 'FH W'",
        description = "=> 'RkggVw=='",
        command = "$DUT -e expected/FH_W.plain FH_W.b64 && diff --binary FH_W.b64 expected/FH_W.b64",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: encode 'FH '",
        description = "=> 'Rkgg'",
        command = "$DUT -e expected/FH_.plain FH_.b64 && diff --binary FH_.b64 expected/FH_.b64",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: encode 'FH'",
        description = "=> 'Rkg='",
        command = "$DUT -e expected/FH.plain FH.b64 && diff --binary FH.b64 expected/FH.b64",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: encode 'F'",
        description = "=> 'Rg=='",
        command = "$DUT -e expected/F.plain F.b64 && diff --binary F.b64 expected/F.b64",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: encode fh_wedel.jpg",
        description = "=> fh_wedel.jpg.b64",
        command = "$DUT -e expected/fh_wedel.jpg fh_wedel.jpg.b64 && diff --binary fh_wedel.jpg.b64 expected/fh_wedel.jpg.b64",
        returnCode = 0,
        timeout = 10
    ),
    
    Test (
        name = "Beispiel: decode 'RkggV2VkZWwh'",
        description = "=> 'FH Wedel!'",
        command = "$DUT -d expected/FH_Wedel_.b64 FH_Wedel_.plain && diff --binary FH_Wedel_.plain expected/FH_Wedel_.plain",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: decode 'RkggV2VkZWw='",
        description = "=> 'FH Wedel'",
        command = "$DUT -d expected/FH_Wedel.b64 FH_Wedel.plain && diff --binary FH_Wedel.plain expected/FH_Wedel.plain",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: decode 'RkggV2VkZQ=='",
        description = "=> 'FH Wede'",
        command = "$DUT -d expected/FH_Wede.b64 FH_Wede.plain && diff --binary FH_Wede.plain expected/FH_Wede.plain",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: decode 'RkggV2Vk'",
        description = "=> 'FH Wed'",
        command = "$DUT -d expected/FH_Wed.b64 FH_Wed.plain && diff --binary FH_Wed.plain expected/FH_Wed.plain",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: decode 'RkggV2U='",
        description = "=> 'FH We'",
        command = "$DUT -d expected/FH_We.b64 FH_We.plain && diff --binary FH_We.plain expected/FH_We.plain",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: decode 'RkggVw=='",
        description = "=> 'FH W'",
        command = "$DUT -d expected/FH_W.b64 FH_W.plain && diff --binary FH_W.plain expected/FH_W.plain",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: decode 'Rkgg'",
        description = "=> 'FH '",
        command = "$DUT -d expected/FH_.b64 FH_.plain && diff --binary FH_.plain expected/FH_.plain",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: decode 'Rkg='",
        description = "=> 'FH'",
        command = "$DUT -d expected/FH.b64 FH.plain && diff --binary FH.plain expected/FH.plain",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: decode 'Rg=='",
        description = "=> 'F'",
        command = "$DUT -d expected/F.b64 F.plain && diff --binary F.plain expected/F.plain",
        returnCode = 0,
        timeout = 10
    ),
    Test (
        name = "Beispiel: decode fh_wedel.jpg.b64",
        description = "=> fh_wedel.jpg",
        command = "$DUT -d expected/fh_wedel.jpg.b64 fh_wedel.jpg && diff --binary fh_wedel.jpg expected/fh_wedel.jpg",
        returnCode = 0,
        timeout = 10
    ),
    
]

EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RF_GPS:NEO-M8N U?
U 1 1 60D8A4F2
P 3150 4250
AR Path="/60D8A4F2" Ref="U?"  Part="1" 
AR Path="/60D892C4/60D8A4F2" Ref="U?"  Part="1" 
F 0 "U?" H 3650 4950 50  0000 C CNN
F 1 "NEO-M8N" H 3500 3550 50  0000 C CNN
F 2 "RF_GPS:ublox_NEO" H 3550 3400 50  0001 C CNN
F 3 "https://www.u-blox.com/sites/default/files/NEO-M8-FW3_DataSheet_%28UBX-15031086%29.pdf" H 3150 4250 50  0001 C CNN
	1    3150 4250
	1    0    0    -1  
$EndComp
Text HLabel 2350 3950 0    50   Input ~ 0
GPS_TX
Text HLabel 2350 4050 0    50   Input ~ 0
GPS_RX
Wire Wire Line
	2350 4050 2450 4050
Wire Wire Line
	2350 3950 2450 3950
NoConn ~ 2450 3650
NoConn ~ 2450 3750
NoConn ~ 2450 4250
NoConn ~ 2450 4350
Text HLabel 2350 4550 0    50   Input ~ 0
GPS_EXTINT
Wire Wire Line
	2350 4550 2450 4550
NoConn ~ 2450 4750
Text HLabel 2350 4850 0    50   Input ~ 0
GPS_RESET
Wire Wire Line
	2350 4850 2450 4850
NoConn ~ 2450 4950
Text HLabel 3950 4550 2    50   Input ~ 0
GPS_TIMEPULSE
Wire Wire Line
	3950 4550 3850 4550
$Comp
L power:GND #PWR?
U 1 1 60E173C8
P 3150 5250
F 0 "#PWR?" H 3150 5000 50  0001 C CNN
F 1 "GND" H 3155 5077 50  0000 C CNN
F 2 "" H 3150 5250 50  0001 C CNN
F 3 "" H 3150 5250 50  0001 C CNN
	1    3150 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 5250 3150 5150
$Comp
L power:GND #PWR?
U 1 1 60E17945
P 3350 2900
F 0 "#PWR?" H 3350 2650 50  0001 C CNN
F 1 "GND" H 3355 2727 50  0000 C CNN
F 2 "" H 3350 2900 50  0001 C CNN
F 3 "" H 3350 2900 50  0001 C CNN
	1    3350 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 3350 3150 2800
Wire Wire Line
	3150 2800 3350 2800
Wire Wire Line
	3350 2800 3350 2900
$Comp
L power:+3V3 #PWR?
U 1 1 60E187D2
P 2650 2750
F 0 "#PWR?" H 2650 2600 50  0001 C CNN
F 1 "+3V3" H 2665 2923 50  0000 C CNN
F 2 "" H 2650 2750 50  0001 C CNN
F 3 "" H 2650 2750 50  0001 C CNN
	1    2650 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 2750 2650 2800
Wire Wire Line
	2650 2800 2950 2800
Wire Wire Line
	2950 2800 2950 3350
$Comp
L power:GND #PWR?
U 1 1 60E19D9C
P 2350 3200
F 0 "#PWR?" H 2350 2950 50  0001 C CNN
F 1 "GND" H 2355 3027 50  0000 C CNN
F 2 "" H 2350 3200 50  0001 C CNN
F 3 "" H 2350 3200 50  0001 C CNN
	1    2350 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60E1A4E4
P 2350 3000
F 0 "C?" H 2442 3046 50  0000 L CNN
F 1 "100nF" H 2442 2955 50  0000 L CNN
F 2 "" H 2350 3000 50  0001 C CNN
F 3 "~" H 2350 3000 50  0001 C CNN
	1    2350 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 3100 2350 3200
Wire Wire Line
	2350 2900 2350 2800
Wire Wire Line
	2350 2800 2650 2800
Connection ~ 2650 2800
NoConn ~ 3850 4050
$Comp
L dk_Coaxial-Connectors-RF:142-0701-801 J?
U 1 1 60E543A4
P 5250 4550
F 0 "J?" H 5162 4518 50  0000 R CNN
F 1 "142-0701-801" H 5162 4427 50  0000 R CNN
F 2 "digikey-footprints:RF_SMA_BoardEdge_142-0701-801" H 5450 4750 60  0001 L CNN
F 3 "http://www.belfuse.com/resources/Johnson/drawings/dr-1420701801.pdf" H 5450 4850 60  0001 L CNN
F 4 "J502-ND" H 5450 4950 60  0001 L CNN "Digi-Key_PN"
F 5 "142-0701-801" H 5450 5050 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 5450 5150 60  0001 L CNN "Category"
F 7 "Coaxial Connectors (RF)" H 5450 5250 60  0001 L CNN "Family"
F 8 "http://www.belfuse.com/resources/Johnson/drawings/dr-1420701801.pdf" H 5450 5350 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/cinch-connectivity-solutions-johnson/142-0701-801/J502-ND/35280" H 5450 5450 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN SMA JACK STR 50OHM EDGE MNT" H 5450 5550 60  0001 L CNN "Description"
F 11 "Cinch Connectivity Solutions Johnson" H 5450 5650 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5450 5750 60  0001 L CNN "Status"
	1    5250 4550
	-1   0    0    -1  
$EndComp
$Comp
L Device:L_Small L?
U 1 1 60E57109
P 4050 3700
F 0 "L?" H 4098 3746 50  0000 L CNN
F 1 "L_Small" H 4098 3655 50  0000 L CNN
F 2 "" H 4050 3700 50  0001 C CNN
F 3 "~" H 4050 3700 50  0001 C CNN
	1    4050 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3350 3350 3200
Wire Wire Line
	3350 3200 3600 3200
Wire Wire Line
	4050 3200 4050 3600
Wire Wire Line
	3850 4250 4050 4250
Wire Wire Line
	4050 4250 4050 3800
Wire Wire Line
	3800 3200 4050 3200
$Comp
L Device:R_Small R?
U 1 1 60E5B23B
P 3700 3200
F 0 "R?" V 3504 3200 50  0000 C CNN
F 1 "R_Small" V 3595 3200 50  0000 C CNN
F 2 "" H 3700 3200 50  0001 C CNN
F 3 "~" H 3700 3200 50  0001 C CNN
	1    3700 3200
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60E5C8AF
P 4600 3350
F 0 "C?" H 4692 3396 50  0000 L CNN
F 1 "C_Small" H 4692 3305 50  0000 L CNN
F 2 "" H 4600 3350 50  0001 C CNN
F 3 "~" H 4600 3350 50  0001 C CNN
	1    4600 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3250 4600 3200
Wire Wire Line
	4600 3200 4050 3200
Connection ~ 4050 3200
$Comp
L power:GND #PWR?
U 1 1 60E5D269
P 4600 3600
F 0 "#PWR?" H 4600 3350 50  0001 C CNN
F 1 "GND" H 4605 3427 50  0000 C CNN
F 2 "" H 4600 3600 50  0001 C CNN
F 3 "" H 4600 3600 50  0001 C CNN
	1    4600 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3600 4600 3450
$Comp
L power:GND #PWR?
U 1 1 60E5E7BC
P 5250 4800
F 0 "#PWR?" H 5250 4550 50  0001 C CNN
F 1 "GND" H 5255 4627 50  0000 C CNN
F 2 "" H 5250 4800 50  0001 C CNN
F 3 "" H 5250 4800 50  0001 C CNN
	1    5250 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 4800 5250 4750
$Comp
L dk_Coaxial-Connectors-RF:U_FL-R-SMT_10_ J?
U 1 1 60E666C0
P 5250 3950
F 0 "J?" V 5282 4038 50  0000 L CNN
F 1 "U_FL-R-SMT_10_" V 5373 4038 50  0000 L CNN
F 2 "digikey-footprints:Coax_Conn_U.FL" H 5450 4150 60  0001 L CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Hirose%20PDFs/UFL%20Series.pdf" H 5450 4250 60  0001 L CNN
F 4 "H9161CT-ND" H 5450 4350 60  0001 L CNN "Digi-Key_PN"
F 5 "U.FL-R-SMT(10)" H 5450 4450 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 5450 4550 60  0001 L CNN "Category"
F 7 "Coaxial Connectors (RF)" H 5450 4650 60  0001 L CNN "Family"
F 8 "https://media.digikey.com/pdf/Data%20Sheets/Hirose%20PDFs/UFL%20Series.pdf" H 5450 4750 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/hirose-electric-co-ltd/U.FL-R-SMT(10)/H9161CT-ND/2135256" H 5450 4850 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN U.FL RCPT STR 50 OHM SMD" H 5450 4950 60  0001 L CNN "Description"
F 11 "Hirose Electric Co Ltd" H 5450 5050 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5450 5150 60  0001 L CNN "Status"
	1    5250 3950
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60E67239
P 5250 4200
F 0 "#PWR?" H 5250 3950 50  0001 C CNN
F 1 "GND" H 5255 4027 50  0000 C CNN
F 2 "" H 5250 4200 50  0001 C CNN
F 3 "" H 5250 4200 50  0001 C CNN
	1    5250 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 4200 5250 4150
Wire Wire Line
	4050 4250 4800 4250
Wire Wire Line
	4800 4250 4800 3950
Wire Wire Line
	4800 3950 5050 3950
Connection ~ 4050 4250
Wire Wire Line
	5050 4550 4800 4550
Wire Wire Line
	4800 4550 4800 4250
Connection ~ 4800 4250
Text Notes 600  800  0    98   Italic 20
Geopositioning System
$Comp
L E22_Radios_Zenith:E22-900M30S U?
U 1 1 60FC2EE1
P 9050 3900
AR Path="/60FC2EE1" Ref="U?"  Part="1" 
AR Path="/60D267AF/60FC2EE1" Ref="U?"  Part="1" 
AR Path="/60D892C4/60FC2EE1" Ref="U?"  Part="1" 
F 0 "U?" H 9050 4765 50  0000 C CNN
F 1 "E22-900M30S" H 9050 4674 50  0000 C CNN
F 2 "E22_Radios_Zenith:E22-900M30S" H 9150 4100 50  0001 C CNN
F 3 "" H 9150 4100 50  0001 C CNN
	1    9050 3900
	1    0    0    -1  
$EndComp
Text HLabel 9700 3950 2    50   Input ~ 0
RADIO_MOSI
Wire Wire Line
	9700 3950 9600 3950
Text HLabel 9700 4050 2    50   Input ~ 0
RADIO_MISO
Text HLabel 9700 4150 2    50   Input ~ 0
RADIO_NRST
Text HLabel 9700 4250 2    50   Input ~ 0
RADIO_BUSY
Wire Wire Line
	9600 4150 9700 4150
Wire Wire Line
	9600 4050 9700 4050
Wire Wire Line
	9700 4250 9600 4250
Text HLabel 9700 4350 2    50   Input ~ 0
RADIO_DIO1
Wire Wire Line
	9600 4350 9700 4350
$Comp
L power:+5V #PWR?
U 1 1 60FC2EF1
P 7700 4100
AR Path="/60D267AF/60FC2EF1" Ref="#PWR?"  Part="1" 
AR Path="/60D892C4/60FC2EF1" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7700 3950 50  0001 C CNN
F 1 "+5V" H 7715 4273 50  0000 C CNN
F 2 "" H 7700 4100 50  0001 C CNN
F 3 "" H 7700 4100 50  0001 C CNN
	1    7700 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 4100 7700 4250
Wire Wire Line
	7700 4250 8500 4250
Wire Wire Line
	8500 4350 7700 4350
Wire Wire Line
	7700 4350 7700 4250
Connection ~ 7700 4250
$Comp
L power:GND #PWR?
U 1 1 60FC2EFC
P 9700 4550
AR Path="/60D267AF/60FC2EFC" Ref="#PWR?"  Part="1" 
AR Path="/60D892C4/60FC2EFC" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 9700 4300 50  0001 C CNN
F 1 "GND" H 9705 4377 50  0000 C CNN
F 2 "" H 9700 4550 50  0001 C CNN
F 3 "" H 9700 4550 50  0001 C CNN
	1    9700 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 4550 9700 4450
Wire Wire Line
	9700 4450 9600 4450
$Comp
L power:GND #PWR?
U 1 1 60FC2F04
P 8400 4550
AR Path="/60D267AF/60FC2F04" Ref="#PWR?"  Part="1" 
AR Path="/60D892C4/60FC2F04" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 8400 4300 50  0001 C CNN
F 1 "GND" H 8405 4377 50  0000 C CNN
F 2 "" H 8400 4550 50  0001 C CNN
F 3 "" H 8400 4550 50  0001 C CNN
	1    8400 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 4550 8400 4450
Wire Wire Line
	8400 4450 8500 4450
$Comp
L power:GND #PWR?
U 1 1 60FC2F0C
P 7700 3550
AR Path="/60D267AF/60FC2F0C" Ref="#PWR?"  Part="1" 
AR Path="/60D892C4/60FC2F0C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7700 3300 50  0001 C CNN
F 1 "GND" H 7705 3377 50  0000 C CNN
F 2 "" H 7700 3550 50  0001 C CNN
F 3 "" H 7700 3550 50  0001 C CNN
	1    7700 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 3550 7700 3500
Wire Wire Line
	7700 3300 8500 3300
Wire Wire Line
	8500 3500 8400 3500
Connection ~ 7700 3500
Wire Wire Line
	7700 3500 7700 3400
Wire Wire Line
	7700 3400 8500 3400
Connection ~ 7700 3400
Wire Wire Line
	7700 3400 7700 3300
Text HLabel 8400 4150 0    50   Input ~ 0
RADIO_DIO2
Text HLabel 8400 4050 0    50   Input ~ 0
RADIO_TXEN
Text HLabel 8400 3950 0    50   Input ~ 0
RADIO_RXEN
Wire Wire Line
	8400 3950 8500 3950
Wire Wire Line
	8400 4050 8500 4050
Wire Wire Line
	8400 4150 8500 4150
Wire Wire Line
	8500 3850 8400 3850
Wire Wire Line
	8400 3850 8400 3750
Connection ~ 8400 3500
Wire Wire Line
	8400 3500 7700 3500
Wire Wire Line
	8500 3750 8400 3750
Connection ~ 8400 3750
Wire Wire Line
	8400 3750 8400 3500
Text HLabel 9700 3750 2    50   Input ~ 0
RADIO_NSS
Wire Wire Line
	9700 3750 9600 3750
Text HLabel 9700 3850 2    50   Input ~ 0
RADIO_SCK
Wire Wire Line
	9600 3850 9700 3850
$Comp
L dk_Coaxial-Connectors-RF:142-0701-801 J?
U 1 1 60FC2F34
P 10550 3400
AR Path="/60D267AF/60FC2F34" Ref="J?"  Part="1" 
AR Path="/60D892C4/60FC2F34" Ref="J?"  Part="1" 
F 0 "J?" H 10462 3368 50  0000 R CNN
F 1 "142-0701-801" H 10800 3550 50  0000 R CNN
F 2 "digikey-footprints:RF_SMA_BoardEdge_142-0701-801" H 10750 3600 60  0001 L CNN
F 3 "http://www.belfuse.com/resources/Johnson/drawings/dr-1420701801.pdf" H 10750 3700 60  0001 L CNN
F 4 "J502-ND" H 10750 3800 60  0001 L CNN "Digi-Key_PN"
F 5 "142-0701-801" H 10750 3900 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 10750 4000 60  0001 L CNN "Category"
F 7 "Coaxial Connectors (RF)" H 10750 4100 60  0001 L CNN "Family"
F 8 "http://www.belfuse.com/resources/Johnson/drawings/dr-1420701801.pdf" H 10750 4200 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/cinch-connectivity-solutions-johnson/142-0701-801/J502-ND/35280" H 10750 4300 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN SMA JACK STR 50OHM EDGE MNT" H 10750 4400 60  0001 L CNN "Description"
F 11 "Cinch Connectivity Solutions Johnson" H 10750 4500 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10750 4600 60  0001 L CNN "Status"
	1    10550 3400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10350 3400 9600 3400
Wire Wire Line
	10050 3300 10050 3500
Wire Wire Line
	10050 3500 9600 3500
Wire Wire Line
	9600 3300 10050 3300
$Comp
L power:GND #PWR?
U 1 1 60FC2F3E
P 10550 3700
AR Path="/60D267AF/60FC2F3E" Ref="#PWR?"  Part="1" 
AR Path="/60D892C4/60FC2F3E" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 10550 3450 50  0001 C CNN
F 1 "GND" H 10555 3527 50  0000 C CNN
F 2 "" H 10550 3700 50  0001 C CNN
F 3 "" H 10550 3700 50  0001 C CNN
	1    10550 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10550 3700 10550 3650
Wire Wire Line
	10050 3500 10350 3500
Wire Wire Line
	10350 3500 10350 3650
Wire Wire Line
	10350 3650 10550 3650
Connection ~ 10050 3500
Connection ~ 10550 3650
Wire Wire Line
	10550 3650 10550 3600
Text Notes 7250 800  0    98   Italic 20
LoRa & (G)FSK 30dBm Radio
Wire Notes Line
	6950 6500 6950 500 
$EndSCHEMATC

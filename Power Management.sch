EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
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
L power:GND #PWR012
U 1 1 60D85621
P 6600 3950
F 0 "#PWR012" H 6600 3700 50  0001 C CNN
F 1 "GND" H 6605 3777 50  0000 C CNN
F 2 "" H 6600 3950 50  0001 C CNN
F 3 "" H 6600 3950 50  0001 C CNN
	1    6600 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 2300 7300 2300
Text HLabel 8650 2500 2    50   Input ~ 0
SDA
Text HLabel 8650 2700 2    50   Input ~ 0
SCL
Text HLabel 8650 2300 2    50   Input ~ 0
ALRT1
Text HLabel 8700 1300 2    50   Input ~ 0
Pack
$Comp
L Device:Thermistor_NTC TH?
U 1 1 60D8563E
P 5500 3450
AR Path="/60D8563E" Ref="TH?"  Part="1" 
AR Path="/60D72946/60D8563E" Ref="TH1"  Part="1" 
F 0 "TH1" H 5597 3496 50  0000 L CNN
F 1 "10k" H 5597 3405 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" H 5500 3500 50  0001 C CNN
F 3 "https://br.mouser.com/ProductDetail/Murata-Electronics/NCU15XH103F6SRC?qs=qSfuJ%252Bfl%2Fd4Hxm3YkwLMjg%3D%3D" H 5500 3500 50  0001 C CNN
	1    5500 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 60D85651
P 6200 3850
F 0 "R7" V 5993 3850 50  0000 C CNN
F 1 "0.01" V 6084 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6130 3850 50  0001 C CNN
F 3 "~" H 6200 3850 50  0001 C CNN
	1    6200 3850
	0    1    -1   0   
$EndComp
Wire Wire Line
	7150 2500 7650 2500
Wire Wire Line
	7150 2700 8000 2700
$Comp
L Device:R_Small R?
U 1 1 60D8567C
P 7300 2000
AR Path="/60D8567C" Ref="R?"  Part="1" 
AR Path="/60D72946/60D8567C" Ref="R14"  Part="1" 
F 0 "R14" H 7359 2046 50  0000 L CNN
F 1 "4.7K" H 7359 1955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 7300 2000 50  0001 C CNN
F 3 "~" H 7300 2000 50  0001 C CNN
	1    7300 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60D85683
P 8000 2000
AR Path="/60D85683" Ref="R?"  Part="1" 
AR Path="/60D72946/60D85683" Ref="R12"  Part="1" 
F 0 "R12" H 8059 2046 50  0000 L CNN
F 1 "4.7K" H 8059 1955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 8000 2000 50  0001 C CNN
F 3 "~" H 8000 2000 50  0001 C CNN
	1    8000 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60D85689
P 7650 2000
AR Path="/60D85689" Ref="R?"  Part="1" 
AR Path="/60D72946/60D85689" Ref="R15"  Part="1" 
F 0 "R15" H 7709 2046 50  0000 L CNN
F 1 "4.7K" H 7709 1955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 7650 2000 50  0001 C CNN
F 3 "~" H 7650 2000 50  0001 C CNN
	1    7650 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60D85697
P 8400 2300
AR Path="/60D85697" Ref="R?"  Part="1" 
AR Path="/60D72946/60D85697" Ref="R16"  Part="1" 
F 0 "R16" V 8204 2300 50  0000 C CNN
F 1 "1K" V 8295 2300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 8400 2300 50  0001 C CNN
F 3 "~" H 8400 2300 50  0001 C CNN
	1    8400 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	8500 2300 8650 2300
Wire Wire Line
	7650 1700 7650 1800
Connection ~ 7650 1800
$Comp
L power:+3V3 #PWR?
U 1 1 60D856B4
P 7650 1700
AR Path="/60D856B4" Ref="#PWR?"  Part="1" 
AR Path="/60D72946/60D856B4" Ref="#PWR013"  Part="1" 
F 0 "#PWR013" H 7650 1550 50  0001 C CNN
F 1 "+3V3" H 7665 1873 50  0000 C CNN
F 2 "" H 7650 1700 50  0001 C CNN
F 3 "" H 7650 1700 50  0001 C CNN
	1    7650 1700
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LD1117S33TR_SOT223 U3
U 1 1 60D979F1
P 9100 5400
F 0 "U3" H 9100 5642 50  0000 C CNN
F 1 "LD1117S33TR_SOT223" H 9100 5551 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 9100 5600 50  0001 C CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000544.pdf" H 9200 5150 50  0001 C CNN
	1    9100 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C9
U 1 1 60D9A0A0
P 5100 2500
F 0 "C9" H 5150 2600 50  0000 L CNN
F 1 "0.1uF" H 5150 2400 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5100 2500 50  0001 C CNN
F 3 "~" H 5100 2500 50  0001 C CNN
	1    5100 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C7
U 1 1 60D9AA24
P 7250 3500
F 0 "C7" H 7300 3600 50  0000 L CNN
F 1 "0.47uF" H 7300 3400 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7250 3500 50  0001 C CNN
F 3 "~" H 7250 3500 50  0001 C CNN
	1    7250 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C11
U 1 1 60DA450D
P 8500 5700
F 0 "C11" H 8550 5800 50  0000 L CNN
F 1 "0.1uF" H 8550 5600 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 8500 5700 50  0001 C CNN
F 3 "~" H 8500 5700 50  0001 C CNN
	1    8500 5700
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C12
U 1 1 60DA4E3C
P 9650 5700
F 0 "C12" H 9700 5800 50  0000 L CNN
F 1 "10uF" H 9700 5600 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 9650 5700 50  0001 C CNN
F 3 "~" H 9650 5700 50  0001 C CNN
	1    9650 5700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 60DA5F25
P 9100 6000
F 0 "#PWR016" H 9100 5750 50  0001 C CNN
F 1 "GND" H 9105 5827 50  0000 C CNN
F 2 "" H 9100 6000 50  0001 C CNN
F 3 "" H 9100 6000 50  0001 C CNN
	1    9100 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 5700 9100 6000
$Comp
L power:GND #PWR015
U 1 1 60DAA209
P 8500 6000
F 0 "#PWR015" H 8500 5750 50  0001 C CNN
F 1 "GND" H 8505 5827 50  0000 C CNN
F 2 "" H 8500 6000 50  0001 C CNN
F 3 "" H 8500 6000 50  0001 C CNN
	1    8500 6000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 60DAA5AA
P 9650 6000
F 0 "#PWR017" H 9650 5750 50  0001 C CNN
F 1 "GND" H 9655 5827 50  0000 C CNN
F 2 "" H 9650 6000 50  0001 C CNN
F 3 "" H 9650 6000 50  0001 C CNN
	1    9650 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 5800 8500 6000
Wire Wire Line
	9650 5800 9650 6000
Wire Wire Line
	9400 5400 9650 5400
Wire Wire Line
	9650 5400 9650 5600
Wire Wire Line
	8500 5600 8500 5400
Wire Wire Line
	8500 5400 8800 5400
$Comp
L power:+3V3 #PWR018
U 1 1 60DB2DA4
P 9900 5250
F 0 "#PWR018" H 9900 5100 50  0001 C CNN
F 1 "+3V3" H 9915 5423 50  0000 C CNN
F 2 "" H 9900 5250 50  0001 C CNN
F 3 "" H 9900 5250 50  0001 C CNN
	1    9900 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 5400 9900 5400
Wire Wire Line
	9900 5400 9900 5250
Connection ~ 9650 5400
$Comp
L Device:R_Small R?
U 1 1 60DF3D23
P 5550 2050
AR Path="/60DF3D23" Ref="R?"  Part="1" 
AR Path="/60D72946/60DF3D23" Ref="R9"  Part="1" 
F 0 "R9" H 5491 2004 50  0000 R CNN
F 1 "10" H 5491 2095 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 5550 2050 50  0001 C CNN
F 3 "~" H 5550 2050 50  0001 C CNN
	1    5550 2050
	-1   0    0    1   
$EndComp
Wire Wire Line
	4000 6550 4000 6450
Wire Wire Line
	4200 6450 4200 6550
Wire Wire Line
	3800 5450 3700 5450
Wire Wire Line
	3700 5450 3700 5350
Wire Wire Line
	3700 5350 3800 5350
$Comp
L Device:C_Small C6
U 1 1 60E78225
P 2050 6300
F 0 "C6" H 1900 6400 50  0000 L CNN
F 1 "10uF" H 1800 6200 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 2050 6300 50  0001 C CNN
F 3 "~" H 2050 6300 50  0001 C CNN
	1    2050 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 6050 3800 6050
NoConn ~ 4600 5750
Wire Wire Line
	4600 5550 4750 5550
Wire Wire Line
	4750 5550 4750 5450
Wire Wire Line
	4750 5350 4600 5350
Wire Wire Line
	4600 5450 4750 5450
Connection ~ 4750 5450
Wire Wire Line
	4750 5450 4750 5350
Connection ~ 4750 5350
$Comp
L Device:C_Small C8
U 1 1 60EDD3EF
P 5250 5600
F 0 "C8" H 5342 5646 50  0000 L CNN
F 1 "2.2uF" H 5342 5555 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 5250 5600 50  0001 C CNN
F 3 "~" H 5250 5600 50  0001 C CNN
	1    5250 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 5500 5250 5350
$Comp
L power:GND #PWR09
U 1 1 60EE21CD
P 5250 5800
F 0 "#PWR09" H 5250 5550 50  0001 C CNN
F 1 "GND" H 5255 5627 50  0000 C CNN
F 2 "" H 5250 5800 50  0001 C CNN
F 3 "" H 5250 5800 50  0001 C CNN
	1    5250 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 5800 5250 5700
$Comp
L Device:CP_Small C10
U 1 1 60EE6DA6
P 5700 5600
F 0 "C10" H 5788 5646 50  0000 L CNN
F 1 "100uF" H 5788 5555 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_5x3" H 5700 5600 50  0001 C CNN
F 3 "~" H 5700 5600 50  0001 C CNN
	1    5700 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 5500 5700 5350
Wire Wire Line
	5700 5350 5250 5350
Connection ~ 5250 5350
$Comp
L power:GND #PWR011
U 1 1 60EEBF1A
P 5700 5800
F 0 "#PWR011" H 5700 5550 50  0001 C CNN
F 1 "GND" H 5705 5627 50  0000 C CNN
F 2 "" H 5700 5800 50  0001 C CNN
F 3 "" H 5700 5800 50  0001 C CNN
	1    5700 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 5800 5700 5700
$Comp
L power:+5V #PWR010
U 1 1 60EF0BEA
P 5700 5200
F 0 "#PWR010" H 5700 5050 50  0001 C CNN
F 1 "+5V" H 5715 5373 50  0000 C CNN
F 2 "" H 5700 5200 50  0001 C CNN
F 3 "" H 5700 5200 50  0001 C CNN
	1    5700 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 5200 5700 5350
Connection ~ 5700 5350
$Comp
L power:+5V #PWR014
U 1 1 60EF9622
P 8500 5250
F 0 "#PWR014" H 8500 5100 50  0001 C CNN
F 1 "+5V" H 8515 5423 50  0000 C CNN
F 2 "" H 8500 5250 50  0001 C CNN
F 3 "" H 8500 5250 50  0001 C CNN
	1    8500 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 5250 8500 5400
Connection ~ 8500 5400
Wire Notes Line
	500  4350 11200 4350
Text Notes 7150 4650 0    98   Italic 20
Linear Voltage Regulator
Text Notes 600  4650 0    98   Italic 20
Synchronous Boost Converter
Text Notes 600  800  0    98   Italic 20
Stand-alone Fuel Gauge
$Comp
L Device:Battery_Cell BT2
U 1 1 61591953
P 4000 2850
F 0 "BT2" H 4118 2946 50  0000 L CNN
F 1 "Battery_Cell" H 4118 2855 50  0000 L CNN
F 2 "Alcantara_v.1:BatteryHolder_Keystone_1042_1x18650_Modified" V 4000 2910 50  0001 C CNN
F 3 "~" V 4000 2910 50  0001 C CNN
	1    4000 2850
	1    0    0    -1  
$EndComp
Text Notes 5700 900  0    50   ~ 0
Retirei os resistores de 150ohms em série com os pinos SDA e SCL antes dos pullup
$Comp
L power:GND #PWR0101
U 1 1 6100DB47
P 4400 6800
F 0 "#PWR0101" H 4400 6550 50  0001 C CNN
F 1 "GND" H 4405 6627 50  0000 C CNN
F 2 "" H 4400 6800 50  0001 C CNN
F 3 "" H 4400 6800 50  0001 C CNN
	1    4400 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 6450 4400 6550
Wire Wire Line
	4100 6450 4100 6550
Wire Wire Line
	4100 6550 4200 6550
Wire Wire Line
	4000 6550 4100 6550
Connection ~ 4100 6550
Wire Wire Line
	4200 6550 4300 6550
Wire Wire Line
	4300 6550 4300 6450
Connection ~ 4200 6550
Wire Wire Line
	4300 6550 4400 6550
Connection ~ 4300 6550
$Comp
L Device:Q_PMOS_GSD Q4
U 1 1 610D18A9
P 4600 1400
F 0 "Q4" V 4942 1400 50  0000 C CNN
F 1 "Q_PMOS_GSD" V 4851 1400 50  0000 C CNN
F 2 "Alcantara_v.1:SOT346" H 4800 1500 50  0001 C CNN
F 3 "~" H 4600 1400 50  0001 C CNN
	1    4600 1400
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 610FCF6D
P 4600 1650
F 0 "#PWR0108" H 4600 1400 50  0001 C CNN
F 1 "GND" H 4605 1477 50  0000 C CNN
F 2 "" H 4600 1650 50  0001 C CNN
F 3 "" H 4600 1650 50  0001 C CNN
	1    4600 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 1650 4600 1600
$Comp
L Regulator_Switching:TPS61092 U2
U 1 1 60DF7C3A
P 4200 5850
F 0 "U2" H 4200 6575 50  0000 C CNN
F 1 "TPS61092" H 4200 6484 50  0000 C CNN
F 2 "Package_DFN_QFN:Texas_S-PVQFN-N16_EP2.7x2.7mm_ThermalVias" H 3250 4800 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/tps61090.pdf" H 4350 4700 50  0001 L CNN
	1    4200 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 6200 2050 5650
Text HLabel 1800 5650 0    50   Input ~ 0
Pack
Connection ~ 2050 5650
Wire Wire Line
	1800 5650 2050 5650
$Comp
L Device:L_Small L1
U 1 1 60E6B8CB
P 3150 5350
F 0 "L1" V 3250 5250 50  0000 R CNN
F 1 "6.8uH" V 3250 5550 50  0000 R CNN
F 2 "SamacSys_Parts:INDPM4040X210N" H 3150 5350 50  0001 C CNN
F 3 "~" H 3150 5350 50  0001 C CNN
	1    3150 5350
	0    1    -1   0   
$EndComp
Wire Wire Line
	3800 5850 3700 5850
Wire Wire Line
	3700 5850 3700 6050
Connection ~ 3700 6050
Wire Wire Line
	4750 5350 5250 5350
Wire Wire Line
	3250 5350 3700 5350
Connection ~ 3700 5350
Wire Wire Line
	2050 5650 2300 5650
Wire Wire Line
	3050 5350 2050 5350
Wire Wire Line
	2050 5350 2050 5650
$Comp
L power:GND #PWR0109
U 1 1 612ACFAF
P 2050 6800
F 0 "#PWR0109" H 2050 6550 50  0001 C CNN
F 1 "GND" H 2055 6627 50  0000 C CNN
F 2 "" H 2050 6800 50  0001 C CNN
F 3 "" H 2050 6800 50  0001 C CNN
	1    2050 6800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 612B0FCE
P 3700 6800
F 0 "#PWR0110" H 3700 6550 50  0001 C CNN
F 1 "GND" H 3705 6627 50  0000 C CNN
F 2 "" H 3700 6800 50  0001 C CNN
F 3 "" H 3700 6800 50  0001 C CNN
	1    3700 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 6800 4400 6550
Connection ~ 4400 6550
Wire Wire Line
	3700 6050 3700 6800
Wire Wire Line
	2050 6400 2050 6800
Wire Wire Line
	2400 6100 2300 6100
Wire Wire Line
	2300 6100 2300 5650
Connection ~ 2300 5650
Wire Wire Line
	2300 5650 3800 5650
Wire Wire Line
	3350 6100 3450 6100
Wire Wire Line
	3450 6100 3450 5750
Wire Wire Line
	3450 5750 3800 5750
NoConn ~ 4600 5850
Text Notes 800  7550 0    50   ~ 0
O componente TLV809ED29DBZR é um surpervisor de tensão com saída push-pull.\nQuando a tensão de alimentação está acima do seu threshold de 2.93V ele leva a sua saída a VCC, habilitando o Boost Converter. \nCaso a tensão em VDD caia abaixo do seu threshold a saída será puxada para 0V, desligando o sistema
Wire Wire Line
	2900 6800 2900 6550
$Comp
L power:GND #PWR0111
U 1 1 612ACC1E
P 2900 6800
F 0 "#PWR0111" H 2900 6550 50  0001 C CNN
F 1 "GND" H 2905 6627 50  0000 C CNN
F 2 "" H 2900 6800 50  0001 C CNN
F 3 "" H 2900 6800 50  0001 C CNN
	1    2900 6800
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:TLV809ED29DBZR IC1
U 1 1 612EBEE6
P 2400 6200
F 0 "IC1" H 2875 6565 50  0000 C CNN
F 1 "TLV809ED29DBZR" H 2875 6474 50  0000 C CNN
F 2 "SamacSys_Parts:SOT95P237X112-3N" H 3450 6300 50  0001 L CNN
F 3 "https://www.ti.com/lit/ds/symlink/tlv809e.pdf?ts=1623232092527&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FTLV809E%253FkeyMatch%253DTLV809EF30DBZR%2526tisearch%253Dsearch-everything%2526usecase%253DOPN" H 3450 6200 50  0001 L CNN
F 4 "Supervisory Circuits Low-power voltage supervisor (reset IC) with active-low, push-pull output 3-SOT-23 -40 to 125" H 3450 6100 50  0001 L CNN "Description"
F 5 "1.12" H 3450 6000 50  0001 L CNN "Height"
F 6 "595-TLV809ED29DBZR" H 3450 5900 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Texas-Instruments/TLV809ED29DBZR?qs=CiayqK2gdcJa0MXo3ZjyIg%3D%3D" H 3450 5800 50  0001 L CNN "Mouser Price/Stock"
F 8 "Texas Instruments" H 3450 5700 50  0001 L CNN "Manufacturer_Name"
F 9 "TLV809ED29DBZR" H 3450 5600 50  0001 L CNN "Manufacturer_Part_Number"
	1    2400 6200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60D85691
P 5500 3050
AR Path="/60D85691" Ref="R?"  Part="1" 
AR Path="/60D72946/60D85691" Ref="R10"  Part="1" 
F 0 "R10" V 5304 3050 50  0000 C CNN
F 1 "10K" V 5395 3050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 5500 3050 50  0001 C CNN
F 3 "~" H 5500 3050 50  0001 C CNN
	1    5500 3050
	-1   0    0    1   
$EndComp
$Comp
L SamacSys_Parts:MAX17201G+T IC2
U 1 1 613217CA
P 5750 2450
F 0 "IC2" H 6450 2865 50  0000 C CNN
F 1 "MAX17201G+T" H 6450 2774 50  0000 C CNN
F 2 "SamacSys_Parts:SON40P300X300X80-15N" H 7000 2550 50  0001 L CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX17201-MAX17215.pdf" H 7000 2450 50  0001 L CNN
F 4 "IC BATT MONITOR 1CELL 14TDFN" H 7000 2350 50  0001 L CNN "Description"
F 5 "0.8" H 7000 2250 50  0001 L CNN "Height"
F 6 "700-MAX17201G+T" H 7000 2150 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Maxim-Integrated/MAX17201G%2bT?qs=6Gr%2FA8Y8f6fpSbQH80s5tg%3D%3D" H 7000 2050 50  0001 L CNN "Mouser Price/Stock"
F 8 "Maxim Integrated" H 7000 1950 50  0001 L CNN "Manufacturer_Name"
F 9 "MAX17201G+T" H 7000 1850 50  0001 L CNN "Manufacturer_Part_Number"
	1    5750 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 2300 5750 2300
Wire Wire Line
	5750 2700 5550 2700
Wire Wire Line
	5750 2600 5550 2600
Wire Wire Line
	5550 2300 5550 2400
Connection ~ 5550 2600
Wire Wire Line
	5550 2600 5550 2700
Wire Wire Line
	5750 2500 5550 2500
Connection ~ 5550 2500
Wire Wire Line
	5550 2500 5550 2600
Wire Wire Line
	5750 2400 5550 2400
Connection ~ 5550 2400
Wire Wire Line
	5550 2400 5550 2500
Wire Wire Line
	4400 1300 4000 1300
Wire Wire Line
	4000 1300 4000 2650
Connection ~ 5550 2300
Wire Wire Line
	6350 3850 6450 3850
Wire Wire Line
	6450 3850 6450 3550
Wire Wire Line
	6450 3850 6600 3850
Wire Wire Line
	6600 3850 6600 3550
Connection ~ 6450 3850
Wire Wire Line
	6600 3950 6600 3850
Connection ~ 6600 3850
Wire Wire Line
	6050 3850 5850 3850
Wire Wire Line
	4000 3850 4000 2950
Wire Wire Line
	6300 3550 6300 3650
Wire Wire Line
	6300 3650 5850 3650
Wire Wire Line
	5850 3650 5850 3850
Connection ~ 5850 3850
Wire Wire Line
	5850 3850 4000 3850
$Comp
L power:GND #PWR0112
U 1 1 61366CA9
P 5500 3600
F 0 "#PWR0112" H 5500 3350 50  0001 C CNN
F 1 "GND" H 5505 3427 50  0000 C CNN
F 2 "" H 5500 3600 50  0001 C CNN
F 3 "" H 5500 3600 50  0001 C CNN
	1    5500 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 3300 5500 3250
Wire Wire Line
	5500 3250 5750 3250
Wire Wire Line
	5500 2950 5500 2900
Wire Wire Line
	5500 2900 5750 2900
Wire Wire Line
	5500 3150 5500 3250
Connection ~ 5500 3250
$Comp
L power:GND #PWR0113
U 1 1 61376F3D
P 5100 2700
F 0 "#PWR0113" H 5100 2450 50  0001 C CNN
F 1 "GND" H 5105 2527 50  0000 C CNN
F 2 "" H 5100 2700 50  0001 C CNN
F 3 "" H 5100 2700 50  0001 C CNN
	1    5100 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 2700 5100 2600
Wire Wire Line
	5100 2400 5100 2300
Wire Wire Line
	5100 2300 5550 2300
Wire Wire Line
	4800 1300 5550 1300
Wire Wire Line
	5550 1950 5550 1300
Connection ~ 5550 1300
Wire Wire Line
	5550 1300 8700 1300
Wire Wire Line
	5550 2150 5550 2300
Wire Wire Line
	7250 3400 7250 3250
Wire Wire Line
	7250 3250 7150 3250
$Comp
L power:GND #PWR0114
U 1 1 6138DA91
P 7250 3950
F 0 "#PWR0114" H 7250 3700 50  0001 C CNN
F 1 "GND" H 7255 3777 50  0000 C CNN
F 2 "" H 7250 3950 50  0001 C CNN
F 3 "" H 7250 3950 50  0001 C CNN
	1    7250 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3950 7250 3600
Wire Notes Line
	6950 6500 6950 4350
Wire Wire Line
	7300 1800 7300 1900
Wire Wire Line
	7300 1800 7650 1800
Wire Wire Line
	8000 1800 8000 1900
Wire Wire Line
	7650 1800 8000 1800
Wire Wire Line
	7650 1900 7650 1800
Wire Wire Line
	7300 2100 7300 2300
Connection ~ 7300 2300
Wire Wire Line
	7300 2300 8300 2300
Wire Wire Line
	7650 2100 7650 2500
Connection ~ 7650 2500
Wire Wire Line
	7650 2500 8650 2500
Wire Wire Line
	8000 2100 8000 2700
Connection ~ 8000 2700
Wire Wire Line
	8000 2700 8650 2700
NoConn ~ 7150 2900
Text Notes 750  2450 0    50   ~ 0
O Mosfet tipo P em série com a bateria faz a função de\nproteção contra polaridade reversa.\n\nCaso a bateria seja invertida ele não conduzirá, protegendo\no circuito.\n\nNão utilizei um zener pois a tensão Vgs máxima permitida\nestá acima da que submeteremos no mosfet.\n\nAlém disso, descartei a necessidade de utilizar um resistor\nno gate, pois esse mosfet ficará constantemente ligado,\nentão o fenômeno de ringing não deve acontecer.\n\nAssitir esse vídeo para saber mais:\nhttps://www.youtube.com/watch?v=IrB-FPcv1Dc
Text Notes 750  3700 0    50   ~ 0
O componente MAX17201 é um monitor de bateria\nde célula única via I2C. Atentar para a diferença com\no MAX17211, que utiliza o protocolo 1-Wire.\n\nEste componente vai fornecer dados como a corrente que flui\npela bateria (por meio do shunt de 0.01ohm) e a tensão nela.\n\nAtentar-se também sobre a diferença com o MAX17205,\nque é um monitor para múltiplas células.
$EndSCHEMATC

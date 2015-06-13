EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:conn_18x2
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "13 jun 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DIL40 P3
U 1 1 557BD120
P 4000 4950
F 0 "P3" H 4000 6000 70  0000 C CNN
F 1 "DIL40" V 4000 4950 60  0000 C CNN
F 2 "~" H 4000 4950 60  0000 C CNN
F 3 "~" H 4000 4950 60  0000 C CNN
	1    4000 4950
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR13
U 1 1 557BDEF7
P 10000 650
F 0 "#PWR13" H 10000 610 30  0001 C CNN
F 1 "+3.3V" H 10000 760 30  0000 C CNN
F 2 "" H 10000 650 60  0000 C CNN
F 3 "" H 10000 650 60  0000 C CNN
	1    10000 650 
	1    0    0    -1  
$EndComp
$Comp
L DTMF_MT8870 P8
U 1 1 557BE323
P 10450 1300
F 0 "P8" V 10400 1450 60  0000 C CNN
F 1 "DTMF_MT8870" V 10500 1450 60  0000 C CNN
F 2 "~" H 10450 1450 60  0000 C CNN
F 3 "~" H 10450 1450 60  0000 C CNN
	1    10450 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 1600 10100 1600
Wire Wire Line
	10100 1500 10000 1500
Connection ~ 10000 1500
$Comp
L CONN_8 P1
U 1 1 557BE38A
P 1450 5650
F 0 "P1" V 1400 5650 60  0000 C CNN
F 1 "CONN_8" V 1500 5650 60  0000 C CNN
F 2 "~" H 1450 5650 60  0000 C CNN
F 3 "~" H 1450 5650 60  0000 C CNN
	1    1450 5650
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR2
U 1 1 557BE399
P 2050 6050
F 0 "#PWR2" H 2050 6050 30  0001 C CNN
F 1 "GND" H 2050 5980 30  0001 C CNN
F 2 "" H 2050 6050 60  0000 C CNN
F 3 "" H 2050 6050 60  0000 C CNN
	1    2050 6050
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR1
U 1 1 557BE3B7
P 2050 5550
F 0 "#PWR1" H 2050 5510 30  0001 C CNN
F 1 "+3.3V" H 2050 5660 30  0000 C CNN
F 2 "" H 2050 5550 60  0000 C CNN
F 3 "" H 2050 5550 60  0000 C CNN
	1    2050 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 5800 1800 5900
Wire Wire Line
	2050 5900 2050 6050
$Comp
L R R14
U 1 1 557BE4B1
P 9350 1550
F 0 "R14" V 9430 1550 40  0000 C CNN
F 1 "R" V 9357 1551 40  0000 C CNN
F 2 "~" V 9280 1550 30  0000 C CNN
F 3 "~" H 9350 1550 30  0000 C CNN
	1    9350 1550
	1    0    0    -1  
$EndComp
$Comp
L R R16
U 1 1 557BE4B7
P 9500 1550
F 0 "R16" V 9580 1550 40  0000 C CNN
F 1 "R" V 9507 1551 40  0000 C CNN
F 2 "~" V 9430 1550 30  0000 C CNN
F 3 "~" H 9500 1550 30  0000 C CNN
	1    9500 1550
	1    0    0    -1  
$EndComp
$Comp
L R R18
U 1 1 557BE4BD
P 9650 1550
F 0 "R18" V 9730 1550 40  0000 C CNN
F 1 "R" V 9657 1551 40  0000 C CNN
F 2 "~" V 9580 1550 30  0000 C CNN
F 3 "~" H 9650 1550 30  0000 C CNN
	1    9650 1550
	1    0    0    -1  
$EndComp
$Comp
L R R20
U 1 1 557BE4C3
P 9800 1550
F 0 "R20" V 9880 1550 40  0000 C CNN
F 1 "R" V 9807 1551 40  0000 C CNN
F 2 "~" V 9730 1550 30  0000 C CNN
F 3 "~" H 9800 1550 30  0000 C CNN
	1    9800 1550
	1    0    0    -1  
$EndComp
$Comp
L R R12
U 1 1 557BE4C9
P 9200 1550
F 0 "R12" V 9280 1550 40  0000 C CNN
F 1 "R" V 9207 1551 40  0000 C CNN
F 2 "~" V 9130 1550 30  0000 C CNN
F 3 "~" H 9200 1550 30  0000 C CNN
	1    9200 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 1100 9650 1300
Wire Wire Line
	9500 1000 9500 1300
Wire Wire Line
	9350 900  9350 1300
Wire Wire Line
	9200 1300 9200 800 
Wire Wire Line
	8850 800  10100 800 
Wire Wire Line
	8950 900  10100 900 
Wire Wire Line
	8650 1000 10100 1000
Wire Wire Line
	8750 1100 10100 1100
Wire Wire Line
	9050 1200 10100 1200
Wire Wire Line
	9800 1200 9800 1300
Wire Wire Line
	9200 1800 9950 1800
Connection ~ 9350 1800
Connection ~ 9500 1800
Connection ~ 9650 1800
Connection ~ 9950 1800
Connection ~ 9800 1800
Wire Wire Line
	10000 1500 10000 650 
Wire Wire Line
	9950 1600 9950 1850
$Comp
L GND #PWR11
U 1 1 557BEAAF
P 9950 1850
F 0 "#PWR11" H 9950 1850 30  0001 C CNN
F 1 "GND" H 9950 1780 30  0001 C CNN
F 2 "" H 9950 1850 60  0000 C CNN
F 3 "" H 9950 1850 60  0000 C CNN
	1    9950 1850
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR12
U 1 1 557BEAD9
P 9750 2250
F 0 "#PWR12" H 9750 2210 30  0001 C CNN
F 1 "+3.3V" H 9750 2360 30  0000 C CNN
F 2 "" H 9750 2250 60  0000 C CNN
F 3 "" H 9750 2250 60  0000 C CNN
	1    9750 2250
	1    0    0    -1  
$EndComp
$Comp
L DTMF_MT8870 P7
U 1 1 557BEADF
P 10200 2900
F 0 "P7" V 10150 3050 60  0000 C CNN
F 1 "DTMF_MT8870" V 10250 3050 60  0000 C CNN
F 2 "~" H 10200 3050 60  0000 C CNN
F 3 "~" H 10200 3050 60  0000 C CNN
	1    10200 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 3200 9850 3200
Wire Wire Line
	9850 3100 9750 3100
Connection ~ 9750 3100
$Comp
L R R13
U 1 1 557BEAE8
P 9100 3150
F 0 "R13" V 9180 3150 40  0000 C CNN
F 1 "R" V 9107 3151 40  0000 C CNN
F 2 "~" V 9030 3150 30  0000 C CNN
F 3 "~" H 9100 3150 30  0000 C CNN
	1    9100 3150
	1    0    0    -1  
$EndComp
$Comp
L R R15
U 1 1 557BEAEE
P 9250 3150
F 0 "R15" V 9330 3150 40  0000 C CNN
F 1 "R" V 9257 3151 40  0000 C CNN
F 2 "~" V 9180 3150 30  0000 C CNN
F 3 "~" H 9250 3150 30  0000 C CNN
	1    9250 3150
	1    0    0    -1  
$EndComp
$Comp
L R R17
U 1 1 557BEAF4
P 9400 3150
F 0 "R17" V 9480 3150 40  0000 C CNN
F 1 "R" V 9407 3151 40  0000 C CNN
F 2 "~" V 9330 3150 30  0000 C CNN
F 3 "~" H 9400 3150 30  0000 C CNN
	1    9400 3150
	1    0    0    -1  
$EndComp
$Comp
L R R19
U 1 1 557BEAFA
P 9550 3150
F 0 "R19" V 9630 3150 40  0000 C CNN
F 1 "R" V 9557 3151 40  0000 C CNN
F 2 "~" V 9480 3150 30  0000 C CNN
F 3 "~" H 9550 3150 30  0000 C CNN
	1    9550 3150
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 557BEB00
P 8950 3150
F 0 "R11" V 9030 3150 40  0000 C CNN
F 1 "R" V 8957 3151 40  0000 C CNN
F 2 "~" V 8880 3150 30  0000 C CNN
F 3 "~" H 8950 3150 30  0000 C CNN
	1    8950 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 2700 9400 2900
Wire Wire Line
	9250 2600 9250 2900
Wire Wire Line
	8950 2900 8950 2400
Wire Wire Line
	8550 2500 9850 2500
Wire Wire Line
	8550 2600 9850 2600
Wire Wire Line
	8550 2700 9850 2700
Wire Wire Line
	8550 2800 9850 2800
Wire Wire Line
	9550 2800 9550 2900
Wire Wire Line
	8950 3400 9700 3400
Connection ~ 9100 3400
Connection ~ 9250 3400
Connection ~ 9400 3400
Connection ~ 9700 3400
Connection ~ 9550 3400
Wire Wire Line
	9750 3100 9750 2250
Wire Wire Line
	9700 3200 9700 3450
$Comp
L GND #PWR10
U 1 1 557BEB18
P 9700 3450
F 0 "#PWR10" H 9700 3450 30  0001 C CNN
F 1 "GND" H 9700 3380 30  0001 C CNN
F 2 "" H 9700 3450 60  0000 C CNN
F 3 "" H 9700 3450 60  0000 C CNN
	1    9700 3450
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR4
U 1 1 557BEB1E
P 6500 650
F 0 "#PWR4" H 6500 610 30  0001 C CNN
F 1 "+3.3V" H 6500 760 30  0000 C CNN
F 2 "" H 6500 650 60  0000 C CNN
F 3 "" H 6500 650 60  0000 C CNN
	1    6500 650 
	-1   0    0    -1  
$EndComp
$Comp
L DTMF_MT8870 P4
U 1 1 557BEB24
P 6050 1300
F 0 "P4" V 6000 1450 60  0000 C CNN
F 1 "DTMF_MT8870" V 6100 1450 60  0000 C CNN
F 2 "~" H 6050 1450 60  0000 C CNN
F 3 "~" H 6050 1450 60  0000 C CNN
	1    6050 1300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6550 1600 6400 1600
Wire Wire Line
	6400 1500 6500 1500
Connection ~ 6500 1500
$Comp
L R R7
U 1 1 557BEB2D
P 7100 1550
F 0 "R7" V 7180 1550 40  0000 C CNN
F 1 "R" V 7107 1551 40  0000 C CNN
F 2 "~" V 7030 1550 30  0000 C CNN
F 3 "~" H 7100 1550 30  0000 C CNN
	1    7100 1550
	-1   0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 557BEB33
P 6950 1550
F 0 "R5" V 7030 1550 40  0000 C CNN
F 1 "R" V 6957 1551 40  0000 C CNN
F 2 "~" V 6880 1550 30  0000 C CNN
F 3 "~" H 6950 1550 30  0000 C CNN
	1    6950 1550
	-1   0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 557BEB39
P 6800 1550
F 0 "R3" V 6880 1550 40  0000 C CNN
F 1 "R" V 6807 1551 40  0000 C CNN
F 2 "~" V 6730 1550 30  0000 C CNN
F 3 "~" H 6800 1550 30  0000 C CNN
	1    6800 1550
	-1   0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 557BEB3F
P 6650 1550
F 0 "R1" V 6730 1550 40  0000 C CNN
F 1 "R" V 6657 1551 40  0000 C CNN
F 2 "~" V 6580 1550 30  0000 C CNN
F 3 "~" H 6650 1550 30  0000 C CNN
	1    6650 1550
	-1   0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 557BEB45
P 7250 1550
F 0 "R9" V 7330 1550 40  0000 C CNN
F 1 "R" V 7257 1551 40  0000 C CNN
F 2 "~" V 7180 1550 30  0000 C CNN
F 3 "~" H 7250 1550 30  0000 C CNN
	1    7250 1550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6800 1100 6800 1300
Wire Wire Line
	6950 1000 6950 1300
Wire Wire Line
	7100 900  7100 1300
Wire Wire Line
	7250 1300 7250 800 
Wire Wire Line
	6400 800  7350 800 
Wire Wire Line
	6400 900  7450 900 
Wire Wire Line
	6400 1000 7550 1000
Wire Wire Line
	6400 1100 7650 1100
Wire Wire Line
	6400 1200 7750 1200
Wire Wire Line
	6650 1200 6650 1300
Wire Wire Line
	6550 1800 7250 1800
Connection ~ 7100 1800
Connection ~ 6950 1800
Connection ~ 6800 1800
Connection ~ 6550 1800
Connection ~ 6650 1800
Wire Wire Line
	6500 1500 6500 650 
Wire Wire Line
	6550 1600 6550 1850
$Comp
L GND #PWR5
U 1 1 557BEB5D
P 6550 1850
F 0 "#PWR5" H 6550 1850 30  0001 C CNN
F 1 "GND" H 6550 1780 30  0001 C CNN
F 2 "" H 6550 1850 60  0000 C CNN
F 3 "" H 6550 1850 60  0000 C CNN
	1    6550 1850
	-1   0    0    -1  
$EndComp
$Comp
L +3.3V #PWR6
U 1 1 557BEB63
P 6600 2250
F 0 "#PWR6" H 6600 2210 30  0001 C CNN
F 1 "+3.3V" H 6600 2360 30  0000 C CNN
F 2 "" H 6600 2250 60  0000 C CNN
F 3 "" H 6600 2250 60  0000 C CNN
	1    6600 2250
	-1   0    0    -1  
$EndComp
$Comp
L DTMF_MT8870 P5
U 1 1 557BEB69
P 6150 2900
F 0 "P5" V 6100 3050 60  0000 C CNN
F 1 "DTMF_MT8870" V 6200 3050 60  0000 C CNN
F 2 "~" H 6150 3050 60  0000 C CNN
F 3 "~" H 6150 3050 60  0000 C CNN
	1    6150 2900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6650 3200 6500 3200
Wire Wire Line
	6500 3100 6600 3100
Connection ~ 6600 3100
$Comp
L R R8
U 1 1 557BEB72
P 7200 3150
F 0 "R8" V 7280 3150 40  0000 C CNN
F 1 "R" V 7207 3151 40  0000 C CNN
F 2 "~" V 7130 3150 30  0000 C CNN
F 3 "~" H 7200 3150 30  0000 C CNN
	1    7200 3150
	-1   0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 557BEB78
P 7050 3150
F 0 "R6" V 7130 3150 40  0000 C CNN
F 1 "R" V 7057 3151 40  0000 C CNN
F 2 "~" V 6980 3150 30  0000 C CNN
F 3 "~" H 7050 3150 30  0000 C CNN
	1    7050 3150
	-1   0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 557BEB7E
P 6900 3150
F 0 "R4" V 6980 3150 40  0000 C CNN
F 1 "R" V 6907 3151 40  0000 C CNN
F 2 "~" V 6830 3150 30  0000 C CNN
F 3 "~" H 6900 3150 30  0000 C CNN
	1    6900 3150
	-1   0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 557BEB84
P 6750 3150
F 0 "R2" V 6830 3150 40  0000 C CNN
F 1 "R" V 6757 3151 40  0000 C CNN
F 2 "~" V 6680 3150 30  0000 C CNN
F 3 "~" H 6750 3150 30  0000 C CNN
	1    6750 3150
	-1   0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 557BEB8A
P 7350 3150
F 0 "R10" V 7430 3150 40  0000 C CNN
F 1 "R" V 7357 3151 40  0000 C CNN
F 2 "~" V 7280 3150 30  0000 C CNN
F 3 "~" H 7350 3150 30  0000 C CNN
	1    7350 3150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6900 2700 6900 2900
Wire Wire Line
	7050 2600 7050 2900
Wire Wire Line
	7200 2500 7200 2900
Wire Wire Line
	7350 2900 7350 2400
Wire Wire Line
	6500 2400 7550 2400
Wire Wire Line
	6500 2500 7650 2500
Wire Wire Line
	6500 2600 7850 2600
Wire Wire Line
	6750 2800 6750 2900
Wire Wire Line
	6650 3400 7350 3400
Connection ~ 7200 3400
Connection ~ 7050 3400
Connection ~ 6900 3400
Connection ~ 6650 3400
Connection ~ 6750 3400
Wire Wire Line
	6600 3100 6600 2250
Wire Wire Line
	6650 3200 6650 3450
$Comp
L GND #PWR7
U 1 1 557BEBA2
P 6650 3450
F 0 "#PWR7" H 6650 3450 30  0001 C CNN
F 1 "GND" H 6650 3380 30  0001 C CNN
F 2 "" H 6650 3450 60  0000 C CNN
F 3 "" H 6650 3450 60  0000 C CNN
	1    6650 3450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8850 800  8850 1900
Wire Wire Line
	8850 1900 8550 1900
Connection ~ 9200 800 
Wire Wire Line
	8950 2000 8950 900 
Connection ~ 9350 900 
Wire Wire Line
	8650 1000 8650 1600
Wire Wire Line
	8650 1600 8550 1600
Connection ~ 9500 1000
Wire Wire Line
	8750 1100 8750 1700
Wire Wire Line
	8750 1700 8550 1700
Connection ~ 9650 1100
Wire Wire Line
	8950 2000 8550 2000
Wire Wire Line
	8550 1800 9050 1800
Wire Wire Line
	9050 1800 9050 1200
Connection ~ 9800 1200
Wire Wire Line
	8550 2900 8950 2900
Connection ~ 8950 2400
Connection ~ 9100 2500
Wire Wire Line
	8950 2400 9850 2400
Wire Wire Line
	9100 2500 9100 2900
Connection ~ 9250 2600
Connection ~ 9400 2700
Connection ~ 9550 2800
Wire Wire Line
	7350 1800 7850 1800
Wire Wire Line
	7350 800  7350 1800
Connection ~ 7250 800 
Wire Wire Line
	7450 1700 7850 1700
Wire Wire Line
	7450 900  7450 1700
Connection ~ 7100 900 
Wire Wire Line
	7550 1600 7850 1600
Wire Wire Line
	7550 1000 7550 1600
Connection ~ 6950 1000
Wire Wire Line
	7650 2000 7850 2000
Wire Wire Line
	7650 1100 7650 2000
Connection ~ 6800 1100
Wire Wire Line
	7750 1200 7750 1900
Wire Wire Line
	7750 1900 7850 1900
Connection ~ 6650 1200
Connection ~ 6750 2800
Connection ~ 6900 2700
Wire Wire Line
	6500 2700 7450 2700
Wire Wire Line
	6500 2800 7450 2800
Connection ~ 7350 2400
Connection ~ 7200 2500
Connection ~ 7050 2600
Wire Wire Line
	7550 2400 7550 2800
Wire Wire Line
	7550 2800 7850 2800
Wire Wire Line
	7450 2800 7450 2900
Wire Wire Line
	7450 2900 7850 2900
Wire Wire Line
	7450 2700 7450 2300
Wire Wire Line
	7450 2300 7750 2300
Wire Wire Line
	7750 2300 7750 2500
Wire Wire Line
	7750 2500 7850 2500
Wire Wire Line
	7650 2500 7650 2700
Wire Wire Line
	7650 2700 7850 2700
$Comp
L CONN_18X2 P2
U 1 1 557C0206
P 2650 4950
F 0 "P2" H 2650 6000 60  0000 C CNN
F 1 "CONN_18X2" V 2650 4950 50  0000 C CNN
F 2 "~" H 2650 4950 60  0000 C CNN
F 3 "~" H 2650 4950 60  0000 C CNN
	1    2650 4950
	1    0    0    -1  
$EndComp
Wire Bus Line
	3550 3750 3550 5800
Wire Bus Line
	2150 3750 4450 3750
Wire Bus Line
	4450 3750 4450 5800
Entry Wire Line
	4350 5900 4450 5800
Entry Wire Line
	4350 5800 4450 5700
Entry Wire Line
	4350 5700 4450 5600
Entry Wire Line
	4350 5600 4450 5500
Entry Wire Line
	4350 5500 4450 5400
Entry Wire Line
	4350 5400 4450 5300
Entry Wire Line
	4350 5300 4450 5200
Entry Wire Line
	4350 5200 4450 5100
Entry Wire Line
	4350 5100 4450 5000
Entry Wire Line
	4350 5000 4450 4900
Entry Wire Line
	4350 4900 4450 4800
Entry Wire Line
	4350 4800 4450 4700
Entry Wire Line
	4350 4000 4450 3900
Entry Wire Line
	4350 4100 4450 4000
Entry Wire Line
	4350 4200 4450 4100
Entry Wire Line
	4350 4300 4450 4200
Entry Wire Line
	4350 4400 4450 4300
Entry Wire Line
	4350 4500 4450 4400
Entry Wire Line
	4350 4600 4450 4500
Entry Wire Line
	4350 4700 4450 4600
Entry Wire Line
	3550 3900 3650 4000
Entry Wire Line
	3550 4000 3650 4100
Entry Wire Line
	3550 4100 3650 4200
Entry Wire Line
	3550 4200 3650 4300
Entry Wire Line
	3550 4300 3650 4400
Entry Wire Line
	3550 4400 3650 4500
Entry Wire Line
	3550 4500 3650 4600
Entry Wire Line
	3550 4600 3650 4700
Entry Wire Line
	3550 4700 3650 4800
Entry Wire Line
	3550 4800 3650 4900
Entry Wire Line
	3550 4900 3650 5000
Entry Wire Line
	3550 5000 3650 5100
Entry Wire Line
	3550 5100 3650 5200
Entry Wire Line
	3550 5200 3650 5300
Entry Wire Line
	3550 5300 3650 5400
Entry Wire Line
	3550 5400 3650 5500
Entry Wire Line
	3550 5500 3650 5600
Entry Wire Line
	3550 5600 3650 5700
Entry Wire Line
	3550 5700 3650 5800
Entry Wire Line
	3550 5800 3650 5900
Wire Bus Line
	2150 3750 2150 5800
Wire Bus Line
	3150 3750 3150 5800
Entry Wire Line
	3050 5900 3150 5800
Entry Wire Line
	3050 5800 3150 5700
Entry Wire Line
	3050 5700 3150 5600
Entry Wire Line
	3050 5600 3150 5500
Entry Wire Line
	3050 5500 3150 5400
Entry Wire Line
	3050 5400 3150 5300
Entry Wire Line
	3050 5300 3150 5200
Entry Wire Line
	3050 5200 3150 5100
Entry Wire Line
	3050 5100 3150 5000
Entry Wire Line
	3050 5000 3150 4900
Entry Wire Line
	3050 4900 3150 4800
Entry Wire Line
	3050 4800 3150 4700
Entry Wire Line
	3050 4000 3150 3900
Entry Wire Line
	3050 4100 3150 4000
Entry Wire Line
	3050 4200 3150 4100
Entry Wire Line
	3050 4300 3150 4200
Entry Wire Line
	3050 4400 3150 4300
Entry Wire Line
	3050 4500 3150 4400
Entry Wire Line
	3050 4600 3150 4500
Entry Wire Line
	3050 4700 3150 4600
Entry Wire Line
	2150 3900 2250 4000
Entry Wire Line
	2150 4000 2250 4100
Entry Wire Line
	2150 4100 2250 4200
Entry Wire Line
	2150 4200 2250 4300
Entry Wire Line
	2150 4300 2250 4400
Entry Wire Line
	2150 4400 2250 4500
Entry Wire Line
	2150 4500 2250 4600
Entry Wire Line
	2150 4600 2250 4700
Entry Wire Line
	2150 4700 2250 4800
Entry Wire Line
	2150 4800 2250 4900
Entry Wire Line
	2150 4900 2250 5000
Entry Wire Line
	2150 5000 2250 5100
Entry Wire Line
	2150 5100 2250 5200
Entry Wire Line
	2150 5200 2250 5300
Entry Wire Line
	2150 5300 2250 5400
Entry Wire Line
	2150 5400 2250 5500
Entry Wire Line
	2150 5500 2250 5600
Entry Wire Line
	2150 5600 2250 5700
Entry Wire Line
	2150 5700 2250 5800
Entry Wire Line
	2050 5700 2150 5800
Connection ~ 2050 5900
$Comp
L DIL40 P6
U 1 1 557C0C18
P 8200 2450
F 0 "P6" H 8200 3500 70  0000 C CNN
F 1 "DIL40" V 8200 2450 60  0000 C CNN
F 2 "~" H 8200 2450 60  0000 C CNN
F 3 "~" H 8200 2450 60  0000 C CNN
	1    8200 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 3400 8550 3600
Wire Wire Line
	7850 3400 7850 3600
$Comp
L GND #PWR9
U 1 1 557C1501
P 8550 3600
F 0 "#PWR9" H 8550 3600 30  0001 C CNN
F 1 "GND" H 8550 3530 30  0001 C CNN
F 2 "" H 8550 3600 60  0000 C CNN
F 3 "" H 8550 3600 60  0000 C CNN
	1    8550 3600
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR8
U 1 1 557C1510
P 7850 3600
F 0 "#PWR8" H 7850 3560 30  0001 C CNN
F 1 "+3.3V" H 7850 3710 30  0000 C CNN
F 2 "" H 7850 3600 60  0000 C CNN
F 3 "" H 7850 3600 60  0000 C CNN
	1    7850 3600
	-1   0    0    1   
$EndComp
Text Notes 9550 750  0    60   ~ 12
DTMF1
Text Notes 6650 750  0    60   ~ 12
DTMF3
Text Notes 9350 2350 0    60   ~ 12
DTMF2
Text Notes 6750 2350 0    60   ~ 12
DTMF4
Text Notes 3150 3650 0    60   ~ 12
Nappe IDE
Text Notes 1750 4750 0    60   ~ 12
Arduino \nMega\n
Text Notes 4550 4800 0    60   ~ 12
Conn\nIDE
Text Notes 8150 1200 0    60   ~ 12
Conn\nIDE
Wire Wire Line
	2050 5700 2050 5550
Wire Wire Line
	2050 5600 1800 5600
Connection ~ 2050 5600
Wire Wire Line
	3050 5900 1800 5900
NoConn ~ 3050 5800
NoConn ~ 2250 5800
NoConn ~ 1800 6000
NoConn ~ 1800 5700
NoConn ~ 1800 5500
NoConn ~ 1800 5400
NoConn ~ 1800 5300
$EndSCHEMATC

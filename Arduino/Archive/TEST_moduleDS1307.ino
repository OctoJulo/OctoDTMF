//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ******************** Test module RTC DS1307 ******************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
/*  Programme test regroupant les fonctions nécessaires, pour 		*/
/*   l'utilisation du module RTC DS1307, avec un arduino MEGA, un	*/		// le brochage I2C se fait sur les broches SDA: 20(Mega) A4(Uno), SCL: 21(Mega) A5(Uno)
/*   shield LCD keypad et logiciel de synchro RTC. (Octo-SynchoRTC)	*/
/*         															*/
/* **************************************************************** */
/*  OctoGeeK					---					Octo Don Julo	*/	
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Bibliothèque ************************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
#include <LiquidCrystal.h>											// Inclusion de la librairie qui permet de gérer un écran lcd. (ici 2x16)
#include <Timer.h>													// Inclusion de la librairie 
#include <Wire.h>													// Inclusion de la librairie Wire pour la gestion de l'I2C.
#include <RTClib.h>													// Inclusion de la librairie Pour le module Temps-réel.
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************ Shield LCD keypad ********************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
// 	--- Le Shield dispose d'un LCD 2x16 et de 5 boutons poussoirs.
#define LCD_D4      			4									//definition des broches LCD du Shield LCD Keypad.
#define LCD_D5      			5
#define LCD_D6      			6
#define LCD_D7      			7
#define LCD_RS     				8
#define LCD_EN      			9

#define boutonRIGHT  			0									//definition des boutons du Shield LCD Keypad.
#define boutonUP     			1
#define boutonDOWN   			2
#define boutonLEFT   			3
#define boutonSELECT 			4
#define boutonNONE   			5

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);	// Brochage du LCD.
int LcdBouton  	= 0;

int read_LCD_boutons()
{
	LcdBouton = analogRead(0);    									// Lecture analogique de la valeur sur broche A0
	// For LCD keypad shield V1.0 :
	if (LcdBouton > 1000) return boutonNONE;
	if (LcdBouton < 50)   return boutonRIGHT;  
	if (LcdBouton < 195)  return boutonUP; 
	if (LcdBouton < 380)  return boutonDOWN; 
	if (LcdBouton < 555)  return boutonLEFT; 
	if (LcdBouton < 790)  return boutonSELECT;   
	return boutonNONE;  											// Quand aucuns boutons n'est utilisé 
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ********************** Shield Datalogging ********************** //			// 	--- Le Shield dispose d'un lecteur SD et d'un RTC DS1307.
// **************************************************************** //			// 	--- Pour l'utilisation sur un Mega, utilisée la bibliothque SC(adafruit mega) et la bibliothque RTClib.
//////////////////////////////////////////////////////////////////////
	RTC_DS1307 RTC; 												// defini le RTC utilisé par la bibliothque.
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// *********************** Variables Internes ********************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////	
// 	---		---			Variables Horodatage			---		--- //
	int secondes;  													// Variable des secondes.
	int minutes;  													// Variable des minutes.
	int heures; 													// Variable des heures.
	int joursemaine; 												// Variable du jour de la semaine.
	int jour;  														// Variable du jour du mois.
	int mois;  														// Variable des mois.
	int annee; 														// Variable des années.
// 	---		---			Variables Comm-Serie			---		--- //
	int octetReception			= 0; 								// Variable de stockage des valeurs reçues sur le port Série. (ASCII)
	char caractereRecu			= 0; 								// Variable pour stockage caractère recu.
	int compt					= 0; 								// Variable comptage caractères reçus.
	String chaineReception		= ""; 								// déclare un objet String vide pour reception chaine.
	bool ValideSerieRTC			= false;							// Variable de validation du 
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// *********************** Progamme Principal ********************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void setup() 
{
    Serial.begin(57600);											// Initialisation de la fonction Serie.
    Wire.begin();													// Initialisation de la fonction I2C.
    RTC.begin();													// Initialisation de la fonction RTC.
	lcd.begin(16, 2);												// Initialise le LCD avec le nb de caractere et le nb de ligne.
    SERIALRTC ();													// Appele du sous-programme de synchronisation par le port COM.
	//RTC.adjust(DateTime(__DATE__, __TIME__)); 					// permet une premiere mise à l'horodatage lors de la programmation.	
	lcd.setCursor(0, 0);											// Place le curseur d'ecriture.
	lcd.print(" TEST RTC ");	 									// Ecrie le message sur le LCD.
	delay(2000);													// Pause de 2 secondes.
	lcd.clear();													// RAZ du LCD.	
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Progamme Boucle ********************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void loop() 
{
AffidateLCD ();
LcdBouton = read_LCD_boutons();										// Lit l'entrée bp shield LCD.	
if (LcdBouton == boutonSELECT)										// Si validée demarre le programme.
	{
		lcd.clear();												// RAZ du LCD.	
		lcd.setCursor(0, 0);										// Place le curseur d'ecriture.
		lcd.print("Reglage RTC");									// Affiche sur le LCD,
		delay(500);													// Temporise.
		SERIALRTC ();												// Programme de maj du RTC
	}
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// *********************** Progamme Interne *********************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void AffidateLCD () 												// Affiche la date et l'heure sur l'ecran LCD.
{	
	DateTime now = RTC.now();										// Déclare la fonction retournant l'horodatage.
	lcd.setCursor(0, 0);											// Place le curseur d'ecriture.
    lcd.print(' ');													// Affiche sur le LCD,
	lcd.print(now.day(), DEC);										// Affiche sur le LCD, le jour.
    lcd.print('/');													// Affiche sur le LCD, le separateur.
    lcd.print(now.month(), DEC);									// Affiche sur le LCD, le mois.	
    lcd.print('/');													// Affiche sur le LCD, le separateur.
	lcd.print(now.year(), DEC);										// Affiche sur le LCD, l'année.
	lcd.setCursor(0, 1);											// Place le curseur d'ecriture.
    lcd.print(' ');													// Affiche sur le LCD,
    lcd.print(now.hour(), DEC);										// Affiche sur le LCD, l'heure.
    lcd.print(':');													// Affiche sur le LCD, le separateur.
    lcd.print(now.minute(), DEC);									// Affiche sur le LCD, les minutes.
    lcd.print(':');													// Affiche sur le LCD, le separateur.
    lcd.print(now.second(), DEC);									// Affiche sur le LCD, les secondes.
    lcd.print(' ');													// Affiche sur le LCD,	
    //lcd.println();
/*	
	Serial.print(now.year(), DEC);									// Support : affichage serie.
    Serial.print('/');												// Support : affichage serie.
    Serial.print(now.month(), DEC);									// Support : affichage serie.
    Serial.print('/');												// Support : affichage serie.
    Serial.print(now.day(), DEC);									// Support : affichage serie.
    Serial.print(' ');												// Support : affichage serie.
    Serial.print(now.hour(), DEC);									// Support : affichage serie.
    Serial.print(':');												// Support : affichage serie.
    Serial.print(now.minute(), DEC);								// Support : affichage serie.
    Serial.print(':');												// Support : affichage serie.
    Serial.print(now.second(), DEC);								// Support : affichage serie.
    Serial.println();												// Retour charriot.
*/
}
//////////////////////////////////////////////////////////////////////
void SERIALRTC () 													// Affiche la date et l'heure sur l'ecran LCD.
{	
	Serial.println('A'); 											// Envoi un "top" au programme de mise à l'heure.
	while (millis()<5000) 											// Attente 5 secondes la liaison série.
	{
		while (Serial.available()>0) 								// Tant qu'un octet est dans la liaison série.
		{ 
				lcd.setCursor(0, 1);								// Place le curseur d'ecriture.
				lcd.print("   RTC encours     ");					// Affiche sur le LCD la synchro en cours.
				delay(500);											// Temporise.
			octetReception=Serial.read(); 							// Lit le 1er octet reçu et le met dans la Variable .     
			if (octetReception==13)  								// Si l'octet reçu est un retour chariot(CR ou 13).
			{
			// 	---		Converti la chaine en entier pour les valeurs de temps
				secondes = int((chaineReception.charAt(0)-48)*10)+int(chaineReception.charAt(1)-48) ;
				minutes = int((chaineReception.charAt(2)-48)*10)+int(chaineReception.charAt(3)-48);
				heures = int((chaineReception.charAt(4)-48)*10)+int(chaineReception.charAt(5)-48);
				joursemaine = 1;
				jour = int((chaineReception.charAt(6)-48)*10)+int(chaineReception.charAt(7)-48);
				mois = int((chaineReception.charAt(8)-48)*10)+int(chaineReception.charAt(9)-48);
				annee = int((chaineReception.charAt(12)-48)*10)+int(chaineReception.charAt(13)-48);			
				
				RTC.adjust(DateTime(annee, mois, jour, heures, minutes, secondes)); 		
				Serial.println("RTC finito");								// Support : affichage serie.
				Serial.println('A'); 								// Envoi un "top" au programme de Fin?
				lcd.setCursor(0, 1);								// Place le curseur d'ecriture.		
				lcd.print("   RTC fin      ");						// Affiche sur le LCD la fin de la synchro.
				delay(500);											// Temporise.
				chaineReception=""; 								// RAZ de la chaine de réception.
				ValideSerieRTC = true;										// Non utilisée ici.
				break; 												// Sort de la boucle while.
			}
			else 													// Si le caractère reçu n'est pas un saut de ligne.
			{ 
				caractereRecu = char(octetReception); 				// Convertit l'octet reçu en caractère.
				chaineReception = chaineReception + caractereRecu; 	// Ajoute le caratère à la chaine.
			}
		}
	}
}

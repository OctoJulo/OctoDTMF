//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ******************** Test Shield Datalogging ******************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
/*  Programme test regroupant les fonctions nécessaires, pour 		*/
/*   l'utilisation du shield Datalogging, avec	Arduino MEGA, un	*/		// le brochage I2C se fait sur les broches SDA: 20(Mega) A4(Uno), SCL: 21(Mega) A5(Uno)
/*   shield LCD keypad et logiciel de synchro RTC. (Octo-SynchoRTC)	*/			
/* **************************************************************** */
/*  OctoGeeK					---					Octo Don Julo	*/	
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Bibliothèque ************************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
#include <LiquidCrystal.h>											// Inclusion de la Bibliothèque qui permet de gérer un écran lcd. (ici 2x16)
#include <Timer.h>													// Inclusion de la Bibliothèque pour la gestion du timer.
#include <Wire.h>													// Inclusion de la Bibliothèque Wire pour la gestion de l'I2C.
#include <SPI.h>													// Inclusion de la Bibliothèque pour la communication SPI.
#include <SD.h>														// Inclusion de la Bibliothèque pour l'utilisation des modules SD. Représentant la carte mémoire SD.
#include <RTClib.h>													// Inclusion de la Bibliothèque Pour le module Temps-réel.
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************ Shield LCD keypad ********************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
	#define LCD_D4      			4								//definition des broches LCD du Shield LCD Keypad.
	#define LCD_D5      			5
	#define LCD_D6      			6
	#define LCD_D7      			7
	#define LCD_RS     				8
	#define LCD_EN      			9

	#define boutonRIGHT  			0								//definition des boutons du Shield LCD Keypad.
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
// ********************** Shield Datalogging ********************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
// 	--- Le Shield dispose d'un lecteur SD et d'un RTC DS1307.
// 	--- Pour l'utilisation sur un Mega, utilisée la bibliothque SC(adafruit mega).
	#define brocheSDCardSelect		4	 							// Broche utilisée pour sélectionner la SD card	(4,8,10)
	#define brocheSDchipSelect		53								// Met la broche(SS)  à 10 (UNO) ou 53 (MEGA) en sortie // Nécessaire avec shield ethernet. 
// 	--- RTC	
	RTC_DS1307 RTC; 												// Defini le RTC utilisé par la bibliothque.
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
	char LaDate					[22]; 								// Variable regroupant la date et l'heure.
// 	---		---			Variables Comm-Serie			---		--- //
	int octetReception			= 0; 								// Variable de stockage des valeurs reçues sur le port Série. (ASCII)
	char caractereRecu			= 0; 								// Variable pour stockage caractère recu.
	int compt					= 0; 								// Variable comptage caractères reçus.
	String chaineReception		= ""; 								// Déclare un objet String vide pour reception chaine.
	bool ValideSerieRTC			= false;							// Variable de validation du 
// 	---		---			Variables Decodeur DTMF			---		--- //
	int DTMF_MES 				= 0;								// Message DTMF decimal.
	char DTMF1 					[14];								// Permet le stockage des octets DTMF sous forme de numero. 14 chiffres Max.
	int count 					= 0;								// Variable pour compteur.
	int Valide 					= 0;								// Variable pour la validation de la reception d'un message (s'incrémente).
// 	---		---				Variables SD				---		--- //
	char nomfichier				[8];								// Permet le stockage du nom du fichier avec horodatage.
	File fichier; 													// Crée un objet fichier.
	File racine; 													// Crée un objet racine.
	Sd2Card card;													// Créé un objet carte.
	
	Timer horloge;													// Initialisation d'un timer. 
	#define Tmax				11									// Valeur max du compteur.
// 	---		---				Variables PERSO				---		--- //	
	String idMateriel			= "OctoDTMF";						// Chaine de caractere pour l'identification.
	String idlogiciel			= "OctoGeeK";						// Chaine de caractere pour l'identification.						
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// *********************** Fonction Internes ********************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////	
byte decToBcd(byte val)												// Convertie un nombre decimal en binaire.
{  	return ( (val/10*16) + (val%10) );	}
byte bcdToDec(byte val)												// Convertie un nombre binaire en decimal.
{	 return ( (val/16*10) + (val%16) );	}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// *********************** Progamme Principal ********************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////	
void setup () 
{
	pinMode(53, OUTPUT);

// --- 		Initialisation shield LCD Keypad.	---	//
	lcd.begin(16, 2);												// Initialise le LCD avec le nb de caractere et le nb de ligne.
	lcd.setCursor(0, 0);											// Place le curseur d'ecriture.
	lcd.print("   Octo-GeeK  ");	 								// Ecrie le message sur le LCD.
	lcd.setCursor(0, 1);											// Place le curseur d'ecriture.
	lcd.print(" Octo-TestSD V1");	 								// Ecrie le message sur le LCD.
	delay(2000);													// Temporise.
	lcd.clear();													// RAZ du LCD.												
// --- 		Initialisation  Serie.				---	//
	Serial.begin(9600); 											// Initialise la vitesse de connexion série à 115200 bauds. // 9600, 19200, 115200			
	Serial.println(" Octo-TestSD "); 										// Support : affichage serie
// --- 		Initialisation du shield datalog.	---	//								
	Wire.begin();													// Initialisation de la liaison I2C. 
	RTC.begin();													// Initialisation de la fonction RTC.
	SynchroPCtoRTC ();												// Appele du sous-programme de synchronisation par le port COM.
	designationfichier(); 											// Appele du sous-programme de désignation du fichier avec horodatage.
	InitSD();														// Appele du sous-programme d'initialisation SD: création de fichier sur la carte utilisant le nom retourné par le sous-programme "designationfichier".											
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Progamme Boucle ********************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void loop () 
{
	AffidateLCD ();													// Appel du sous-programme de visualisation LCD de la date et l'heure. 
}
////////////////////////////////////////////////////////////////////// OK
//////////////////////////////////////////////////////////////////////		// n'appele pas de sous programme, usilise SD.h et RTClib.h
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
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void designationfichier() 											// Retourne une chaine de caractere pour la désignation du fichier. // Format: "MMJJDTMF.txt"
{
	DateTime now 	= RTC.now();									// Déclare la fonction retournant l'horodatage.
	int jour  		= now.day();									// Variable du jour du mois.
	int mois  		= now.month();									// Variable des mois.
	sprintf(nomfichier,"%02d%02dDTMF.txt",mois,jour);				// Crée le nom du fichier avec l'horodatage. // 8 caractères max (nom) . 3 caractères max(extention)
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void RebootSD()														// Ajoute dans le fichier(nomfichier) l'horodatage du reboot.
{
	fichier = SD.open(nomfichier, FILE_WRITE);						// Ouvre le fichier en ecriture.
	DateTime now 	= RTC.now();									// Déclare la fonction retournant l'horodatage.
	int secondes  	= now.second();									// Variable des secondes.
	int minutes  	= now.minute();									// Variable des minutes.
	int heures 		= now.hour();									// Variable des heures.
	int jour  		= now.day();									// Variable du jour du mois.
	int mois  		= now.month();									// Variable des mois.
	int annee 		= now.year();
	sprintf(LaDate,"%02d/%02d/%04d - %02d:%02d:%02d",jour,mois,annee,heures,minutes,secondes);// Crée la chaine d'horodatage.	// Format: "JJ/MM/AAAA - HH:MM:SS"
	
	//horodatage();													// 
	fichier.print("Reboot : ");										// Ecrie dans le fichier "reboot"
	fichier.println(LaDate);										// Ecrie dans le fichier la date et l'heure.
	fichier.close();												// 
}
//////////////////////////////////////////////////////////////////////	OK
//////////////////////////////////////////////////////////////////////		// n'appele pas de sous programme, usilise SD.h et RTClib.h
void InitSD() 														// Initialisation de la carte SD et de la création du fichier ".txt"
{	
	if (!SD.begin(10,11,12,13)) 									// Si la bibliothque SD ne s'initialise pas.
	{
		Serial.println("initialisation ratee!");							// Support : affichage serie.
		return;														// Sort de la boucle.
	}
	Serial.println("initialisation ok.");									// Support : affichage serie.
// 	--- fichier horodaté
	//designationfichier();
	if (SD.exists(nomfichier)) 										// Si le fichier horodaté est déja présent.
	{
		Serial.print(nomfichier);											// Support : affichage serie.
		Serial.println(" deja present.");									// Support : affichage serie.
		RebootSD();													// Appel du sous-programme de LOG dans le fichier principale.
	}
	else 
	{
		fichier = SD.open(nomfichier, FILE_WRITE);					// Crée le fichier uniquement si il n'existe pas.
		Serial.print("Creation du fichier : ");								// Support : affichage serie.
		Serial.println(nomfichier);											// Support : affichage serie.
		fichier.println("//---------- OctoGeeK - DTMF V1 ----------//");	// Entête.
		fichier.println(LaDate);											// nom du fichier.
		fichier.println("--------------------------------------------");	// Séparateur entête.
		fichier.println("Date - heure ; N° du Detecteur ; MessageDTMF");	// Format du tableau.
		fichier.println("--------------------------------------------");	// Séparateur entête.	
		fichier.close();	
	}
}

//////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////// marche PAS !
void horodatage()													//
{
	DateTime now 	= RTC.now();									// Déclare la fonction retournant l'horodatage.
	int secondes  	= now.second();									// Variable des secondes.
	int minutes  	= now.minute();									// Variable des minutes.
	int heures 		= now.hour();									// Variable des heures.
	int jour  		= now.day();									// Variable du jour du mois.
	int mois  		= now.month();									// Variable des mois.
	int annee 		= now.year();
	sprintf(LaDate,"%02d/%02d/%04d - %02d:%02d:%02d",jour,mois,annee,heures,minutes,secondes);
	//sprintf(LaDate,"%02d/%02d/%04d",jour,mois,annee);
	Serial.println(LaDate);													// Support : affichage serie.
}
//////////////////////////////////////////////////////////////////////	OK
//////////////////////////////////////////////////////////////////////
void SynchroPCtoRTC()												// Affiche la date et l'heure sur l'ecran LCD.
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

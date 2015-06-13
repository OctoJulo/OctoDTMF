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
// ********** Constantes, Variables, Fonctions Internes *********** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
// 	---		---			Variables Comm-Serie			---		--- //
	int octetReception			= 0; 								// Variable de stockage des valeurs reçues sur le port Série. (ASCII)
	char caractereRecu			= 0; 								// Variable pour stockage caractère recu.
	int compt					= 0; 								// Variable comptage caractères reçus.
	String chaineReception		= ""; 								// Déclare un objet String vide pour reception chaine.
// 	---		---				Variables Timer				---		--- //
	Timer horloge;													// Initialisation d'un timer. 
	#define Tmax				11									// Valeur max du compteur.
//////////////////////////////////////////////////////////////////////
// ********************** Module DTMF DFrobot ********************* //
//////////////////////////////////////////////////////////////////////
// 	---		---		Constantes brochages module DTMF	---		--- //
	#define DTMF_B1      			38								// LSD								
	#define DTMF_B2      			36								// --- message binaire
	#define DTMF_B4      			34								// --- DTMF
	#define DTMF_B8      			32								// MSB
	#define DTMF_Str     			30								// Bit Strobe (a 1 si DTMF detecté)
// 	---		---			Variables Decodeur DTMF			---		--- //
	int DTMF_MES 				= 0;								// Message DTMF decimal.
	char DTMF1 					[14];								// Permet le stockage des octets DTMF sous forme de numero. 14 chiffres Max.
	int count 					= 0;								// Variable pour compteur.
	int Valide 					= 0;								// Variable pour la validation de la reception d'un message (s'incrémente).
//////////////////////////////////////////////////////////////////////
// ************************ Shield LCD keypad ********************* //
//////////////////////////////////////////////////////////////////////
// 	---		---		Constantes brochages LCD 2x16		---		--- //	
	#define LCD_D4      			4								// Definition des broches LCD du Shield LCD Keypad.
	#define LCD_D5      			5
	#define LCD_D6      			6
	#define LCD_D7      			7
	#define LCD_RS     				8
	#define LCD_EN      			9

	#define boutonRIGHT  			0								// Definition des boutons du Shield LCD Keypad.
	#define boutonUP     			1
	#define boutonDOWN   			2
	#define boutonLEFT   			3
	#define boutonSELECT 			4
	#define boutonNONE   			5
	LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);	// Brochage du LCD.
// 	---				Variables des 5 boutons poussoirs			--- //	
	int LcdBouton  	= 0;
	int read_LCD_boutons()
	{
		LcdBouton = analogRead(0);    								// Lecture analogique de la valeur sur broche A0
		// For LCD keypad shield V1.0 :
		if (LcdBouton > 1000) return boutonNONE;
		if (LcdBouton < 50)   return boutonRIGHT;  
		if (LcdBouton < 195)  return boutonUP; 
		if (LcdBouton < 380)  return boutonDOWN; 
		if (LcdBouton < 555)  return boutonLEFT; 
		if (LcdBouton < 790)  return boutonSELECT;   
		return boutonNONE;  										// Quand aucuns boutons n'est utilisé 
	}
//////////////////////////////////////////////////////////////////////
// ********************** Shield Datalogging ********************** //
//////////////////////////////////////////////////////////////////////
// 	--- Le Shield dispose d'un lecteur SD et d'un RTC DS1307.
// 	--- Pour l'utilisation sur un Mega, utilisée la bibliothque SC(adafruit mega).
	#define brocheSDCardSelect		4	 							// broche utilisée pour sélectionner la SD card	(4,8,10)
	#define brocheSDchipSelect		53								// Met la broche(SS)  à 10 (UNO) ou 53 (MEGA) en sortie // Nécessaire avec shield ethernet. 

// 	--- 	---					RTC						---		--- //
	RTC_DS1307 RTC; 
// 	---		---				Variables SD				---		--- //
	File fichier;													// Crée un objet fichier.
	File racine;													// Crée un objet racine.
    char nomfichier				[8];								// Permet le stockage du nom du fichier avec horodatage.
// 	---		---			Variables Horodatage			---		--- //
	int secondes;  													// Variable des secondes.
	int minutes;  													// Variable des minutes.
	int heures; 													// Variable des heures.
	int joursemaine; 												// Variable du jour de la semaine.
	int jour;  														// Variable du jour du mois.
	int mois;  														// Variable des mois.
	int annee; 														// Variable des années.
	char LaDate					[22]; 								// Variable regroupant la date et l'heure.
	int ValidSynchro;												// Variable de reception serie de la validation pour la synchro.
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// *********************** Progamme Principal ********************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////	
void setup () 
{
// --- 		Initialisation entrée/Sortie.		---	//
	pinMode(53, OUTPUT);

// --- 			Initialisation Serie.			---	//	
	Serial.begin(57600);											// Initialise la vitesse de connexion série à 115200 bauds. // 9600, 19200, 115200	
	Serial.println("Initialisation SD...");									// Support : affichage serie
	Serial.println(" Octo-TEST SD"); 										// Support : affichage serie	
// --- 		Initialisation du shield datalog.	---	//
    Wire.begin();													// Initialisation de la fonction I2C.
    RTC.begin();													// Initialisation de la fonction RTC.
	SynchroPCtoRTC ();												// Appel du sous-programme de synchronisation du DS1307 par le port serie (logiciel).
// --- 		Initialisation shield LCD Keypad.	---	//
	lcd.begin(16, 2);												// Initialise le LCD avec le nb de caractere et le nb de ligne.
	lcd.setCursor(0, 0);											// Place le curseur d'ecriture.
	lcd.print("   Octo-GeeK  ");	 								// Ecrie le message sur le LCD.
	lcd.setCursor(0, 1);											// Place le curseur d'ecriture.
	lcd.print(" Octo-TEST SD ");	 								// Ecrie le message sur le LCD.
	delay(2000);													// Temporise.
	lcd.clear();													// RAZ du LCD.	
	
// --- 		Initialisation SD et fichier.		---	//
	designationfichier(); 											// Appel du sous-programme créant le nom du fichier.
	SDInit();														// Appel du sous-programme d'initialisation de la SD.
	Serial.println("debut du programme.");									// Support : affichage serie.
	
// --- 			Initialisation du Timer. 		---// 
	//horloge.every (940, compteur);	

}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Progamme Boucle ********************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void loop () 
{
	//horloge.update();
	AffidateLCD ();													// Appel du sous-programme de visualisation LCD de la date et l'heure. 
	ValidSynchro = Serial.read();
	if(ValidSynchro == 65)											// Correspond à la reception d'un A.
	{
	/*	lcd.setCursor(0,0);
		lcd.print("XXXXXXXXXXXXXXXX");
		lcd.setCursor(0,1);
		lcd.print("XXXXXXXXXXXXXXXX");
		delay(2000);
		lcd.clear();
	*/	
		Serial.println('B'); 											// Envoi un "top" au programme de mise à l'heure.
		delay(100);
		SynchroPCtoRTC2();
	}
	
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************ Programme DTMF ************************ //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////	OK
// ************************* Décodeur DTMF ************************ //
//////////////////////////////////////////////////////////////////////
void DetectDTMF() 													// Détection et décodage DTMF.
{	
	if (Valide == 0)												// Si aucun message n'a etait recu depuis Tmax.
	{		Valide = 1;					}
	Serial.println(" message dtmf recu "); 									// Support : affichage serie. 
	if (digitalRead(DTMF_B1) == HIGH)								// Met a 1 si le bit 1 est détecté. ou pas.
	{ 		DTMF_MES = 1;  				} 
	else 
	{ 		DTMF_MES = 0;  				} 
	if (digitalRead(DTMF_B2) == HIGH)								// Ajoute 2 si le bit 2 est détecté. ou pas.
	{		DTMF_MES = DTMF_MES + 2;  	} 
	if (digitalRead(DTMF_B4) == HIGH)								// Ajoute 4 si le bit 4 est détecté. ou pas.
	{ 		DTMF_MES = DTMF_MES + 4;  	} 
	if (digitalRead(DTMF_B8) == HIGH)								// Ajoute 8 si le bit 8 est détecté. ou pas.
	{ 		DTMF_MES = DTMF_MES + 8;  	}
	Serial.println(DTMF_MES);												// Support : affichage serie du nombre recu.
	lcd.print(DTMF_MES);											// Affichage LCD du nombre recu.
	delay(200);
}
//////////////////////////////////////////////////////////////////////	OK
// ******************* Compteur de message DTMF ******************* //
//////////////////////////////////////////////////////////////////////
void compteur ()													// Incrémente une valeur si elle n'est pas nul toutes les secondes.
{
	if (Valide !=0)
	{		Valide++;		}
}
//////////////////////////////////////////////////////////////////////	OK
// ***************** Mise en forme du message DTMF **************** //
//////////////////////////////////////////////////////////////////////
void miseenformemessage()											// Sous programme stockant le message DTMF dans un tableau
{
	if(DTMF_MES==10)												// 0
	{	DTMF_MES = 48;			}									// ascii 48
	else if(DTMF_MES==11)											// * 
	{	DTMF_MES = 42;			}									// ascii 42
	else if(DTMF_MES==12)											// #
	{	DTMF_MES = 35;			}									// ascii 35
	else
	{	DTMF_MES = DTMF_MES+48;	}									// Ajoute 48 pour la convertion ascii.
	DTMF1 [count] = DTMF_MES;										// Ajoute la valeur recu dans le tableau.	
	if(count < 13)//13?												// Si le compteur est inferieur à la derniere cellule du tableau.
	{	count ++;				}									// Incemente le compteur.
	if(count == 13)//13?											// Si le compteur est égal à la derniere cellule du tableau.
	{	SauvegardeSD();			}									// Appele le sous-programme SauvegardeSD.
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************ Programme RTC ************************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////	NOK
// ********************** Chaine horodatage  ********************** //
//////////////////////////////////////////////////////////////////////
void horodatage()													//Crée la chaine de caractère d'horodatage.	// format: JJ/MM/AAAA - hh:mm:ss .
{
	DateTime now 	= RTC.now();									// Retourne l'horodatage du RTC.
	int secondes  	= now.second();									// Variable des secondes.
	int minutes  	= now.minute();									// Variable des minutes.
	int heures 		= now.hour();									// Variable des heures.
	int jour  		= now.day();									// Variable du jour du mois.
	int mois  		= now.month();									// Variable des mois.
	int annee 		= now.year();
	sprintf(LaDate,"%02d/%02d/%04d - %02d:%02d:%02d",jour,mois,annee,heures,minutes,secondes);
}
//////////////////////////////////////////////////////////////////////	OK
// ********************** Affichage horodaté  ********************* //
////////////////////////////////////////////////////////////////////// N'appele pas de sous programme, usilise SD.h et RTClib.h
void AffidateLCD () 												// Affiche la date et l'heure sur l'ecran LCD.
{		
	DateTime now = RTC.now();										// Déclare la fonction retournant l'horodatage.
	lcd.setCursor(0, 0);											// Place le curseur d'ecriture.
    lcd.print(' ');													// Affiche sur le LCD.
	lcd.print(now.day(), DEC);										// Affiche sur le LCD, le jour.
    lcd.print('/');													// Affiche sur le LCD, le separateur.
    lcd.print(now.month(), DEC);									// Affiche sur le LCD, le mois.	
    lcd.print('/');													// Affiche sur le LCD, le separateur.
	lcd.print(now.year(), DEC);										// Affiche sur le LCD, l'année.
	lcd.setCursor(0, 1);											// Place le curseur d'ecriture.
    lcd.print(' ');													// Affiche sur le LCD.
    lcd.print(now.hour(), DEC);										// Affiche sur le LCD, l'heure.
    lcd.print(':');													// Affiche sur le LCD, le separateur.
    lcd.print(now.minute(), DEC);									// Affiche sur le LCD, les minutes.
    lcd.print(':');													// Affiche sur le LCD, le separateur.
    lcd.print(now.second(), DEC);									// Affiche sur le LCD, les secondes.
    lcd.print(' ');													// Affiche sur le LCD.	
}
//////////////////////////////////////////////////////////////////////	OK
// ***************** Synchronisation du DS1307  ******************* //
//////////////////////////////////////////////////////////////////////
void SynchroPCtoRTC2()												// Affiche la date et l'heure sur l'ecran LCD.
{	
		while (Serial.available()>0) 								// Tant qu'un octet est dans la liaison série.
		{ 
			lcd.setCursor(0, 1);									// Place le curseur d'ecriture.
			lcd.print("   RTC encours     ");						// Affiche sur le LCD la synchro en cours.
			//delay(500);											// Temporise.
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
				Serial.println('C'); 								// Envoi un "top" au programme de Fin?
				lcd.setCursor(0, 1);								// Place le curseur d'ecriture.		
				lcd.print("   RTC fin      ");						// Affiche sur le LCD la fin de la synchro.
				delay(500);											// Temporise.
				chaineReception=""; 								// RAZ de la chaine de réception.
				break; 												// Sort de la boucle while.
			}
			else 													// Si le caractère reçu n'est pas un saut de ligne.
			{ 
				caractereRecu = char(octetReception); 				// Convertit l'octet reçu en caractère.
				chaineReception = chaineReception + caractereRecu; 	// Ajoute le caratère à la chaine.
			}
		}
		Serial.println('C'); 								// Envoi un "top" au programme de Fin?
	}
}

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
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Programme SD ************************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////	OK
// *********************** Initialisation SD ********************** //
//////////////////////////////////////////////////////////////////////
void SDInit() 														// Initialise la création du fichier sur la carte SD.
{
	if (!SD.begin(10,11,12,13))										// Si l'initialisation n'a pas eu lieu.
	{
		Serial.println("initialisation SD ratee!");							// Support: affichage serie.
		lcd.setCursor(0, 0);										// Place le curseur d'ecriture.
		lcd.print(" initialisation ");	 							// Ecrie le message sur le LCD.
		lcd.setCursor(0, 1);										// Place le curseur d'ecriture.
		lcd.print("     SD NOK     ");	 							// Ecrie le message sur le LCD.
		delay(2000);												// Temporise.
		lcd.clear();												// RAZ du LCD.
		return;														// Sort de la boucle.
	}
	Serial.println("initialisation ok.");									// Support: affichage serie.
// 	--- fichier horodaté
	if (SD.exists(nomfichier)) 										// Si le fichier est presen sur la carte SD.
	{
		Serial.print(nomfichier);											// Support: affichage serie.
		Serial.println(" deja present.");									// Support: affichage serie.
		SDreboot();													// Appele le sous-programme d'indication du reboot.
	}
	else 
	{
		fichier = SD.open(nomfichier, FILE_WRITE);					// Crée le fichier uniquement si il n'existe pas.
		Serial.print("Creation du fichier : ");								// Support : affichage serie.
		Serial.println(nomfichier);											// Support : affichage serie.
		fichier.println("//-------- OctoGeeK - OctoDTMF Va --------//");// Entête.
		//fichier.println(LaDate);									// nom du fichier.
		fichier.println("--------------------------------------------");// Séparateur entête.
		fichier.println("Date - heure ; N° du Detecteur ; MessageDTMF");// Format du tableau.
		fichier.println("--------------------------------------------");// Séparateur entête.	
		fichier.close();											// Ferme le fichier.
	}
}
//////////////////////////////////////////////////////////////////////	OK
// *********************** Reboot fichier SD ********************** //
//////////////////////////////////////////////////////////////////////
void SDreboot()														// Ecrie dans le programme la date et l'heure du reboot.
{
	fichier = SD.open(nomfichier, FILE_WRITE); 						// Ouvre le fichier en écriture.
	DateTime now 	= RTC.now();									// Retourne l'horodatage du RTC.
	int secondes  	= now.second();									// Variable des secondes.
	int minutes  	= now.minute();									// Variable des minutes.
	int heures 		= now.hour();									// Variable des heures.
	int jour  		= now.day();									// Variable du jour du mois.
	int mois  		= now.month();									// Variable des mois.
	int annee 		= now.year();
	sprintf(LaDate,"%02d/%02d/%04d - %02d:%02d:%02d",jour,mois,annee,heures,minutes,secondes);
	fichier.print("Reboot : ");										// Ecrie "reboot" dans le fichier.
	fichier.println(LaDate);										// Ecrie l'horodatage. 
	fichier.close();												// Ferme le fichier.
}
//////////////////////////////////////////////////////////////////////	OK
// *********************** Nom du fichier SD ********************** //
//////////////////////////////////////////////////////////////////////
void designationfichier() 											// Crée une chaine de caractère pour le nom du fichier.	// Format: MMJJDTMF.txt
{
	DateTime now 	= RTC.now();									// Retourne l'horodatage du RTC.
	int jour  		= now.day();									// Variable du jour du mois.
	int mois  		= now.month();									// Variable des mois.
	sprintf(nomfichier,"%02d%02dDTMF.txt",mois,jour);				//
}
//////////////////////////////////////////////////////////////////////	OK
// ********************* Sauvegarde fichier SD ******************** //
//////////////////////////////////////////////////////////////////////
void SauvegardeSD() 
{	
	count 	=	0;													// Initialise le compteur à 0.
	Valide  = 	0; 													// Initialise le temps de validation à 0.
	fichier = SD.open(nomfichier, FILE_WRITE); 						// Ouvre le fichier en écriture.
	Serial.println ("Enregistrement en cours :");							// Support: affichage serie.
	Serial.println (DTMF1);													// Support: Message recu.
// 			--- Format d'enregistrement dans le fichier ---			//
// 		---|Date - heure ; N° du Detecteur ; MessageDTMF|---		//
	DateTime now 	= RTC.now();									// Retourne l'horodatage du RTC.
	int secondes  	= now.second();									// Variable des secondes.
	int minutes  	= now.minute();									// Variable des minutes.
	int heures 		= now.hour();									// Variable des heures.
	int jour  		= now.day();									// Variable du jour du mois.
	int mois  		= now.month();									// Variable des mois.
	int annee 		= now.year();									// Variable des années.
	sprintf(LaDate,"%02d/%02d/%04d - %02d:%02d:%02d",jour,mois,annee,heures,minutes,secondes);
	fichier.print(LaDate);											// ecrie l'horodatage. 	
	fichier.print(" ; ");											// Séparateur du tableau.
	fichier.print("NumDTMF");										// Numéro du DTMF.
	fichier.print(" ; ");											// Séparateur du tableau.	
	fichier.print(DTMF1);											// Message recu.
	fichier.println("");											// Saut de ligne.
    fichier.close(); 												// ferme le fichier.
	Serial.println ("Fichier Ferme");										// Support : affichage serie.
}



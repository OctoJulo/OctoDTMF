
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ********************* Projet - Processing  ********************* //	Version testée et validée.
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
/*  Programme de synchronisation du RTC par le port COM.			*/
/* **************************************************************** */
/*																	*/
/* **************************************************************** */
/*  Version: alpha				---				Date: 08/11/2014	*/	
/*  OctoGeeK					---				Octo Don Julo		*/	
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Bibliothèque ************************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
import controlP5.*;													// Bibliothèque de control : bp, liste etc...
import processing.serial.*;											// Bibliothèque pour la gestion serie. 
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ********** Constantes, Variables, Fonctions Internes *********** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
//  ---     		   CLASS      		  ---  //
	OctoGeek appel;                                        			// Permet l'appel de fonction la CLASS OctoGeek.
	Octohorlogerie appel2;
	ControlP5 cp5;													// Permet l'appel de fonction la Bibliothèque ControlP5.
//  ---     		   Serie     		  ---  //   
	Serial monPortCOM;												// Nom donné au port Serie.
	DropdownList ListCOMchoix;              						//Definie le nom de la variable pour le choix du port COM par Dropdownlist.
	String[] ListCOMvalide ;               							// Variable comportant les ports COM valides.
	boolean InitSerie;               								// Valeur de test pour l'initialisation du port serie.
	boolean COMSelection = false;     								// Valeur de test pour la selection d'un port COM.  
  	int COMChoisi;													// Variable stockant le numéro du port COM choisi.
	String dataReading      	= "";
	String input       			= "";   
//  ---    		    OctoGeeK 		      ---  //
	boolean	ValideId			= false; 
	String VartextCOM  = "Choisir le port COM:";
	String oldVartextCOM= "";
	int hauteurtext = 200;
//  ---    		    Horloge 		      ---  //  
	int oldsecond      = second();
	char inByte; 
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// *********************** Progamme Principal ********************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
public void setup()
{
	cp5 = new ControlP5(this);             				    		//
	cp5.setColorBackground( color( 0,0,0 ) );                 		//	Donne la couleur de control cp5.(noire)
    cp5.setColorLabel ( color( 255,255,0 ));                 		//	Donne la couleur des label cp5.(jaune)
	size(800, 600);  												// Definie une fenetre de 800x600.
	background(74,107,140);                                     	// Definie la couleur du fond. (gris-bleu claire)
    appel =new OctoGeek();                                     		// Appele la CLASS OctoGeek.
	appel2	= new Octohorlogerie();									// Appele la CLASS Octohorlogerie.
	cp5.addButton("Synchro-RTC")                              		// Creer un bouton pour la synchroRTC
		.setPosition(180,105)										// Définie la position.
		.setSize(80,50)												// Définie la taille.
	;
	cp5.addButton("RAZ-RTC")                              			// Creer un bouton pour le RAZ du RTC
		.setPosition(300,105)										// Définie la position.
		.setSize(80,50)												// Définie la taille.	
	;	
	cp5.addButton("Exit")                              				// Creer un bouton Exit.
		.setPosition(730,95)										// Définie la position. 
		.setSize(60,60)												// Définie la taille.	
	;
	ListCOMchoix = cp5.addDropdownList("list-1",180,20,150,84);		// Creer une dropdown list. 			// ("name", left margin, top margin, width, height (84 here since the boxes have a height of 20, and theres 1 px between each item so 4 items (or scroll bar).
	customize(ListCOMchoix);  										// Appele la fonction customize qui définie les valeurs de la liste. 
//  ---    		    bloc d'affichage serie:
	stroke(0,0,0);                         							// Donne une couleur (contour) a l'objet qui suit.(noire)
	strokeWeight(2);												// Definie l'epaisseur du contour.
	fill(255, 255, 255);											// Donne une couleur au fond.(blanc)
	rect(10, 180, 200, 410);                    					// Dessine un réctangle.					//This is more pratical if you have several list that needs the same settings.	
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// *********************** Progamme Affichage ********************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
public void draw()
{
	appel.OctoLogo();                                       		// Appele la fonction horloge du CLASS Octogeek.
	appel2.horlogeNUM();
	Affichtext();
	while(COMSelection == true && InitSerie == false)				// So when we have chosen a Serial port but we havent yet setup the Serial connection. Do this loop
	{		InitialisationCOMSerie(ListCOMvalide); 			}		// Appele InitialisationCOMSerie, fonction retournant la valeur du port COM choisi. 
}

//////////////////////////////////////////////////////////////////////
// ******************* Affichage Zone de texte ******************** //
//////////////////////////////////////////////////////////////////////
void Affichtext() 
{
	if (VartextCOM != oldVartextCOM)								// boucle affichage si change.
    {
		fill(33,69,92);												// Donne une couleur aux textes
		text(VartextCOM, 15,hauteurtext);							// Ecrit le texte.	
		hauteurtext =hauteurtext + 15;								// Incrémente la position du texte.
        VartextCOM = oldVartextCOM;									// Stock la variable dans une autre variable
        if(hauteurtext>= 600)										//	
		{
			stroke(0,0,0);                         					// Donne une couleur (contour) a l'objet qui suit.(noire)
			strokeWeight(2);										// Definie l'epaisseur du contour.
			fill(255, 255, 255);									// Donne une couleur au fond.(blanc)
			rect(10, 180, 200, 410);                    			// Dessine un réctangle.							
			hauteurtext=200;										// Place le curseur d'ecriture au debut.
		}  
	}
}
//////////////////////////////////////////////////////////////////////
// ************************ Liste Port COM ************************ //
//////////////////////////////////////////////////////////////////////
void customize(DropdownList ddl) 
{
	ddl.setBackgroundColor(color(200));  							// Donne la couleur de l'arriere fond de la liste.
	ddl.setItemHeight(20);  										// Définie la taille des objet de la liste lorsque elle est ouverte.
	ddl.setBarHeight(15);  											// Set the height of the bar itself.
	ddl.captionLabel().set("Selection port COM");  					// Définie le nom de la liste.
	ddl.captionLabel().style().marginTop = 3;  						// Définie la marge haute  du nom.
	ddl.captionLabel().style().marginLeft = 3;  					// Définie la marge gauche du nom.
	ddl.valueLabel().style().marginTop = 3;  						// Définie la marge haute  des objets.
	ListCOMvalide = monPortCOM.list();  							// Stock la valeur des ports COM valides.
	String comlist = join(ListCOMvalide, ",");						// We need to know how many ports there are, to know how many items to add to the list, so we will convert it to a String object (part of a class).
	String COMlist = ListCOMvalide[0];								// We also need how many characters there is in a single port name, we´ll store the chars here for counting later.
	int size2 = COMlist.length();									// Here we count the length of each port name.
	int size1 = comlist.length() / size2;							// Now we can count how many ports there are, well that is count how many chars there are, so we will divide by the amount of chars per port name.
	for(int i=0; i< size1; i++)										// Ajoute les ports COM valides dans la liste. //How many items is determined by the value of size1.
	{   
		ddl.addItem(ListCOMvalide[i],i);							//This is the line doing the actual adding of items, we use the current loop we are in to determin what place in the char array to access and what item number to add it as.
	}
	ddl.setColorBackground(color(60));  							// Donne la couleur de l'arriere fond des objets.
	ddl.setColorActive(color(255,128));		  						// Donne la couleur des objets lorsque le curseur est dessus.
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ********************* Initialisation Serie ********************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void InitialisationCOMSerie(String[] theport)
{
	monPortCOM = new Serial(this, theport[COMChoisi], 57600);		// Initialisation de port COM utilisé. 
	InitSerie = true;			  
	VartextCOM = "Réglage arduino ";
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************ Evenement Serie *********************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void serialEvent(Serial monPortCOM) 
{
/*	
	VartextCOM= monPortCOM.readString();							// pour debug.
	Affichtext();								
*/
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// *********************** Evenement Control ********************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void controlEvent(ControlEvent theEvent) 
{
	if (theEvent.isGroup())
	{
		//	---		Menu déroulant port Serie
		if (theEvent.group().name()=="list-1")						// Si la liste change.
		{
			COMChoisi = int(theEvent.group().value());			    // Stock la valeur selectionnée dans la liste du port COM. Store the value of which box was selected, we will use this to acces a string (char array).
			COMSelection = true;									// 
			VartextCOM = "Port serie choisi: "+Serial.list()[COMChoisi];
            println(VartextCOM);											// Support: Affiche		
		}
	}
	else if(theEvent.isController()) 
	{
		//	---		bouton Synchro-RTC
		if (theEvent.controller().name()=="Synchro-RTC")         	// Si le bouton SynchroRTC est appuyé.
		{
			VartextCOM ="Synchro-RTC2...";
			Affichtext();											// Affiche dans la zone d'info.
			String joinedTime =nf(second(),2)+nf(minute(),2)+nf(hour(),2)+nf(day(),2)+nf(month(),2)+str(year()); // formate la chaine en mettant un '0' devant les unités
			//println (joinedTime);                         		// Envoi la chaine dans le terminal.
			monPortCOM.write (joinedTime+"\r");             		// Envoi la chaine suivie d'un retour chariot sur le port série.
			VartextCOM = "Heure envoyée : ";
			Affichtext();											// Affiche dans la zone d'info.
			VartextCOM = joinedTime;								// Met l'horodatage dans la variable"affichagetexte".
			Affichtext();											// Affiche dans la zone d'info.
		}		
		//	---		bouton RAZ RTC  (13/07/2000 - 13:07:00)
		if (theEvent.controller().name()=="RAZ-RTC")             	// Si le bouton Exit est appuyé.
		{		 		
			VartextCOM ="RAZ-RTC...";
			Affichtext();											// Affiche dans la zone d'info.
			String joinedTime = "00071313072000";					// Format du RAZ
			monPortCOM.write (joinedTime+"\r");             		// Envoi la chaine suivie d'un retour chariot sur le port série.
			VartextCOM = "RAZ envoyé : ";
			Affichtext();											// Affiche dans la zone d'info.
			VartextCOM = joinedTime;								// Met l'horodatage dans la variable"affichagetexte".
			Affichtext();											// Affiche dans la zone d'info.
			VartextCOM ="fin RAZ";
		}		
		//	---		bouton Exit 
		if (theEvent.controller().name()=="Exit")             		// Si le bouton Exit est appuyé.
		{		exit(); 		}									// Execute la fonction exit qui quitte le programme. 	
	}
}



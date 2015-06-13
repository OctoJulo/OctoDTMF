//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ********************* CLASS - Processing  ********************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
class OctoGeek 
{
  //  ---      Variable    ---  //
	PImage Logo;
	OctoGeek()
	{
		Logo = loadImage("OctoLogo.png");							// Va chercher l'image du logo dans le dossier du programme.	
	}
//////////////////////////////////////////////////////////////////////
// ***************************** Logo  **************************** //
//////////////////////////////////////////////////////////////////////	
	void OctoLogo()			
	{
	// affichage du cadre
	fill(33,69,92);													// Donne une couleur (remplissage) a l'objet qui suit.(gris-bleu nuit)
	stroke(0,0,0);													// Donne une couleur (contour) a l'objet qui suit.(noire)
	strokeWeight(2);												// definit l'épaisseur du contour. 	
	rect(0, 0, 800, 165);											// rectangle.
	line(170,0,170,165);
	// affichage du Logo
		image(Logo, 5, 5, width/5, height/4);						// Affiche le logo en haut a droite (en taille réduite =160*160pixel) 
	
	// affichage du nom du logiciel
		fill(255,170,0); 					// Donne une couleur (remplissage) a l'objet qui suit.(orange)
		textFont(createFont("Verdana", 32));
		text("OctoDTMF", width/2, 50);	
	
	// affichage de "marque"
		fill(82,0,204);					// Donne une couleur (remplissage) a l'objet qui suit.(violet)
		textFont(createFont("Verdana", 15));
		text("Powered by GRM", 660, 595);
    }	
}

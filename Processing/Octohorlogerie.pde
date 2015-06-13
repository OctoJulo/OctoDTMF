//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ********************* CLASS - Processing  ********************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
class Octohorlogerie 
{
  //  ---      Variable horloge    ---  //
  int circlex, circley;
  float secondsRadius;
  float minutesRadius;
  float hoursRadius;
  float clockDiameter;
	Octohorlogerie()
	{
		int radius 		= min(width, height) / 4;
		secondsRadius 	= radius * 0.72;
		minutesRadius 	= radius * 0.60;
		hoursRadius 	= radius * 0.50;
		clockDiameter 	= radius * 1.4;
		circlex 		= 70;
		circley 		= 70;										
	}
//////////////////////////////////////////////////////////////////////
// ********************** Horloge numérique  ********************** //
//////////////////////////////////////////////////////////////////////	
	void horlogeNUM()
	{
		fill(20,20,20);           								// Donne une couleur (remplissage) au rectangle.  	(grisatre)           							
		stroke(200,200,200);												// Donne une couleur (contour) au rectangle.(blanchatre)		
		strokeWeight(2);
		rect(650,10,130,50);											// Crée un rectangle débutant et de taille(debutx,debuty,taillex,tailley)	
		fill(255,170,0);           									// Donne une couleur au texte.						(orange)
		text(hour()+" : "+minute()+" : "+second(), 660, 50);
		text(day()+" / "+month()+" / "+year(), 660, 30);
	
	}
//////////////////////////////////////////////////////////////////////
// ********************** Horloge analogique  ********************* //
//////////////////////////////////////////////////////////////////////	 
	void horlogeANA()
	{	
		// dessine l'horloge (en gris)
		fill(80);													// Donne une couleur.
		noStroke();													
		ellipse(circlex, circley, clockDiameter, clockDiameter);				// Dessine le cercle de l'horloge		
		// Angles for sin() and cos() start at 3 o'clock;
		// subtract HALF_PI to make them start at the top
		float s = map(second(), 0, 60, 0, TWO_PI) - HALF_PI;
		float m = map(minute() + norm(second(), 0, 60), 0, 60, 0, TWO_PI) - HALF_PI; 
		float h = map(hour() + norm(minute(), 0, 60), 0, 24, 0, TWO_PI * 2) - HALF_PI;		
		// Draw the hands of the clock
		stroke(255);													// Donne une couleur.
		strokeWeight(1);												// Donne une épaisseur à l'aiguille. 
		line(circlex, circley, circlex + cos(s) * secondsRadius, circley + sin(s) * secondsRadius);		// Dessine l'aiguille des secondes.
		strokeWeight(2);												// Donne une épaisseur à l'aiguille.
		line(circlex, circley, circlex + cos(m) * minutesRadius, circley + sin(m) * minutesRadius);		// Dessine l'aiguille des minutes.
		strokeWeight(4);												// Donne une épaisseur à l'aiguille.
		line(circlex, circley, circlex + cos(h) * hoursRadius, circley + sin(h) * hoursRadius);			// Dessine l'aiguille des heures.		
		// Draw the minute ticks
		strokeWeight(2);
		beginShape(POINTS);
		for (int a = 0; a < 360; a+=6) 
		{
			float angle = radians(a);
			float x = circlex + cos(angle) * secondsRadius;
			float y = circley + sin(angle) * secondsRadius;
			vertex(x, y);
		}
		endShape();
	}
}

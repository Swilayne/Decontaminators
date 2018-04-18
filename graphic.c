/**
 * \file		graphic.c 
 * \version		rendu2
 * \date		2018-04-10
 * \author		Nal et Leafe
 * \brief		Programme pour le projet du cours Programmation II
 *            
 *
 */
 
// *******************************************************************
// 		inclusion de fichiers en-tête avec la directives include

#include <stdio.h>
#include <math.h>
#include <GL/glu.h>
#include "graphic.h"
#include "utilitaire.h"

void graphic_draw_segment (S2D p1, S2D p2)
{ 
    glBegin (GL_LINES);

    glVertex2f (p1->x, p1->y);
    glVertex2f (p2->x, p2->y);

    glEnd ();
}

void graphic_draw_circle (C2d cercle, int filled)
{ 
	int i; 
	float alpha,x,y;
	const int SIDES = 500;
	
	if (filled == GRAPHIC_FILLED)
		glBegin (GL_POLYGON);
	else
		glBegin (GL_LINE_LOOP);
  
	for (i=0; i < SIDES; i++)
    {
		alpha = i * 2. * M_PI / SIDES;
		x = cercle->centre->x + cercle->rayon * cos (alpha), 
		y = cercle->centre->y + cercle->rayon * sin (alpha); 
		glVertex2f (x, y); 
	}
	
	glEnd ();
}

/********************************************************************/
/*	affichage.cpp                                                   */
/*  Auteur : E. Thé, session A26                                    */
/*                                                                  */
/*	Description: Pour l'affichage des points et des liens entre eux */
/********************************************************************/
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include "affichage.h"
#include "winbgim.h"      //la librairie graphique à inclure au projet

// MACRO pour inverser une coordonnée-Y. La position 0 sera au BAS de l'écran.
#define INV_Y(y)  (MAX_Y - (y) + 5)     //avec une marge de 5 pixel en haut

/********************************************************************/
/*                     Définition des fonctions                     */
/********************************************************************/
//Ouverture du mode graphique  
void mode_graphique(void) {
	int carte = DETECT;  //Pour initialisation du mode graphique
	int mode;

	initgraph(&carte, &mode, "");

	//Fermer le programme si y'a erreur à l'initalisation graphique
	if (graphresult() != grOk)
		exit(1);

	//Initialisation de l'écran graphique
	cleardevice();
}

/********************************************************************/
//Fermeture du mode graphique   
void fermer_mode_graph(void) {
	closegraph();
}

/********************************************************************/
//Permet d'effacer l'écran   
void nettoyer_ecran(void) {
	cleardevice();
}

/********************************************************************/
//Permet de savoir si une touche vient d'être pesée dans la console graphique
int  touche_pesee(void) {
	return kbhit_graph();
}

/********************************************************************/
//Permet de faire une pause-écran   
void pause_ecran(void) {
	//afficher le message-pause au bas de l'écran
	settextstyle(0, HORIZ_DIR, 2);	    //avec une police plus grande
	setcolor(WHITE);
	outtextxy(100, MAX_Y + 50, "Appuyer une touche pour continuer..");
	getch_graph();						//attends une touche..

	settextstyle(0, HORIZ_DIR, 1);      //remettre la taille par défaut
}

/********************************************************************/
//Permet de faire attendre le programme pendant "msec" millisecondes
void delai_ecran(int msec) {
	delay_graph(msec);
}

/********************************************************************/
//Dessine un petit point à la position-écran (x, y) avec le "no" affiché à coté
//NOTE: la coordonnée "y" sera inverséé (avec la position 0 au BAS de l'écran)
void dessiner_pt(int x, int y, int no) {
    char val[5] = { 0 };     //string pour la conversion de "no" en caractères

    setcolor(WHITE);
    circle(x, INV_Y(y), 2);  //avec coord. y inversée et un rayon de 2 pixels
    _itoa(no, val, 10);      //conversion base 10 de "no" dans la string "val"
    outtextxy(x + 1, INV_Y(y) + 1, val);      //avec coord. y inversée
}

/********************************************************************/
//Dessine une ligne jaune du point (x, y) au point (x2, y2)
//NOTE: la coordonnée "y" sera inverséé (avec la position 0 au BAS de l'écran)
void dessiner_lig(int x, int y, int x2, int y2) {
	setcolor(YELLOW);

	line(x, INV_Y(y), x2, INV_Y(y2));  //avec coord. y inversées
}

/********************************************************************/
//Efface la ligne déssinée du point (x, y) au point (x2, y2) (ligne en NOIR)
//NOTE: la coordonnée "y" sera inverséé (avec la position 0 au BAS de l'écran)
void effacer_lig(int x, int y, int x2, int y2) {
	setcolor(BLACK);

	line(x, INV_Y(y), x2, INV_Y(y2));  //avec coord. y inversées
}

/********************************************************************/
/********************************************************************/
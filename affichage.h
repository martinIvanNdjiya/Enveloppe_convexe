/********************************************************************/
/*	INF147 - Travail pratique #1                                    */
/*	affichage.h                                                     */
/*  Auteur : E. Thé, session A26                                    */
/*                                                                  */
/*	Description: Pour l'affichage des points et des liens entre eux */
/********************************************************************/
#ifndef MAX_X     //permet d'éviter la double-compilation du module

//Deux constantes qui déterminent la taille du plan d'affichage des points
#define  MAX_Y  800
#define  MAX_X  1400

/********************************************************************/
/*                   Déclarations des fonctions                     */
/********************************************************************/

//Ouverture du mode graphique.
void mode_graphique(void);

//Fermeture du mode graphique.
void fermer_mode_graph(void);

//Permet d'effacer l'écran.
void nettoyer_ecran(void);

//Permet de savoir si une touche vient d'être pesée dans la console graphique.
//Retour de 1 si oui, 0 sinon (aucune touche vient d'être pesée).
int  touche_pesee(void);

//Permet de faire attendre le programme pendant "msec" millisecondes.
void delai_ecran(int msec);

//Permet de faire une pause-écran (jusqu'à une touche soit pesée).
//Un message de pause-écran sera affiché au bas de l'écran.
void pause_ecran(void); 

//Dessine un petit point à la position-écran (x, y) avec le "no" affiché à coté.
//NOTE: la coordonnée "y" sera inverséé (avec la position 0 au BAS de l'écran)
void dessiner_pt(int x, int y, int no);

//Dessine une ligne jaune du point (x, y) au point (x2, y2).
//NOTE: la coordonnée "y" sera inverséé (avec la position 0 au BAS de l'écran)
void dessiner_lig(int x, int y, int x2, int y2);

// Efface la ligne déssinée du point(x, y) au point(x2, y2) (ligne en NOIR).
//NOTE: la coordonnée "y" sera inverséé (avec la position 0 au BAS de l'écran)
void effacer_lig(int x, int y, int x2, int y2);

#endif
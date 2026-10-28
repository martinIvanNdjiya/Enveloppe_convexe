#define _CRT_SECURE_NO_WARNINGS 
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tab_points.h"
#include "affichage.h"


/*=========================================================*/
/*=================== FONCTIONS ===========================*/

/* SWAP */
void swap(t_point* a, t_point* b) {
    t_point tampon = *a;
    *a = *b;
    *b = tampon;
}

/* VERIFIER_DOUBLONS */
int verifier_doublons(const t_point tab_pts[], int taille_actuelle, int y_aleatoire) {
    int j;
    for (j = 0; j < taille_actuelle; j++) {
        if (tab_pts[j].posy == y_aleatoire) {
            return 0; // Trouvé un doublon (pas unique)
        }
    }
    return 1; // Aucun doublon, le y est unique
}
/* DISTANCE */
double distance(t_point * pA, t_point * pB){
    double diffx = pB->posx - pA->posx;
    double diffy = pB->posy - pA->posy;
    return sqrt (diffx *  diffx) + (diffy * diffy);
}

/* PROD_VECTORIEL */
double prod_vectoriel(t_point * p0, t_point * p1, t_point * p2){
    double a = p1->posx - p0->posx;
    double b = p2->posx - p0->posx;
    double c = p1->posy - p0->posy;
    double d = p2->posy - p0->posy;

    return (a*d) - (b*c);
}

/* COORD_POLAIRE */
double coord_polaire(t_point * pA, t_point * pB, t_point * h_ref){
    double dist = distance(pA, pB);
    double angle = asin((pB->posy - pA->posy) / dist);
    double produitVectoriel = prod_vectoriel(pA, h_ref, pB);

    if (produitVectoriel > 0.0) {
        return angle;
    } else if (produitVectoriel < 0.0) {
        return angle + 2 *(M_PI/2 - angle);
    } else {
        return angle;
    }
}

/* ALEA */ 
// RENDRE STATIC
int alea(int min, int max){    
    //retourne un entier aléatoire dans [min, max]
	return (rand() % (max - min + 1) + min);
}

/* INIT_TAB_ALEA */
void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy) {
    int i;
    int y_aleatoire;

    for (i = 0; i < taille; i++) {
        tab_pts[i].posx = alea(1, maxx);

        // Répéter la génération tant que le y n'est pas unique
        do {
            y_aleatoire = alea(1, maxy);
        } while (verifier_doublons(tab_pts, i, y_aleatoire) == 0);

        tab_pts[i].posy = y_aleatoire;
    }
}

/* TROUVER_PT_MINIMAL */
int trouver_pt_minimal(const t_point tab_pts[], int taille){
    int i; //compteur
    int indice = 0;            //prendre premiere valeur comme etant le min

    for (i = 1; i < taille; i++)			 //pour toutes les autres valeurs
        if (tab_pts[i].posy < tab_pts[indice].posy) 
            indice = i;  

        else if (tab_pts[i].posy == tab_pts[indice].posy &&
                 tab_pts[i].posx < tab_pts[indice].posx) {
                indice = i;
            }
   
	return indice;
}

/* PLACER_PT_REFERENCE */
t_point placer_pt_reference(t_point tab_pts[], int pos_min){
    tab_pts[0].rad = 0; //Initialisation de l'angle radian
    tab_pts[0].dist = 0; //Initialisation de la distance

    // Permuter le point minimal avec la case 0 du tableau 
    swap(&tab_pts[0], &tab_pts[pos_min]);    

    // Creer le point h_ref  (meme posx, posy = 800)
    t_point h_ref;
    h_ref.posx = tab_pts[0].posx;
    h_ref.posy = MAX_Y;     

    return h_ref;
}

/* CALCUL_COORD_POLAIRES A TESTER*/
void calcul_coord_polaires(t_point tab_pts[], int taille, t_point* ref) {
    int i; // compteur

    // Point minimal a la case 0 --> pointeur vers l'adresse de la case 0 de tab_pts
    t_point * pMin = &tab_pts[0];

    // On parcourt des points a partir du deuxieme 
    for (i = 1; i < taille; i++) {
        // Calcul de la distance relative au point minimal
        tab_pts[i].dist = distance(pMin, &tab_pts[i]);

        // Calcul de l'angle polaire relatif au point minimal et ref
        tab_pts[i].rad = coord_polaire(pMin, &tab_pts[i], ref);
    }
}

/* TRIER_PTS */ 
void trier_pts(t_point tab_pts[], int taille)
{
    int i, j, indice;
    t_point tampon;

    // On commence à 1 : le point en [0] reste à sa place
    for (i = 1; i < taille - 1; i++)
    {
        indice = i; // position du min. courant

        for (j = i + 1; j < taille; j++)
        {
            if (tab_pts[j].rad < tab_pts[indice].rad ||
                (tab_pts[j].rad == tab_pts[indice].rad &&
                    tab_pts[j].dist < tab_pts[indice].dist))
            {
                indice = j;
            }
        }

        // Permuter une seule fois, après avoir trouvé le min.
        if (indice != i)
        {
            swap(&tab_pts[i], &tab_pts[indice]);
        }
    }
}

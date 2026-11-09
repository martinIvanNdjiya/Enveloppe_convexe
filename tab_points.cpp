/************************************************************************************
Par    : Martin Ivan Ndjiya et Judith Andrasko
Date   : Octobre 2026

Ce module implémente les fonctions de calcul géométrique, de génération aléatoire et
de tri des points nécessaires pour l'algorithme de l'enveloppe convexe.
On y retrouve les sous-programmes suivants :
- swap                 : Permute deux structures de points.
- verifier_doublons    : Vérifie si une ordonnée est déjà présente pour éviter les doublons.
- distance             : Calcule la distance euclidienne entre deux points.
- prod_vectoriel       : Calcule le produit vectoriel de deux vecteurs.
- coord_polaire        : Calcule l'angle polaire relatif à l'axe horizontal.
- alea                 : Génère un entier aléatoire dans un intervalle [min, max].
- init_tab_alea        : Initialise un tableau de points avec des coordonnées aléatoires uniques en y.
- trouver_pt_minimal   : Trouve l'indice du point minimal (plus petit y, puis plus petit x).
- placer_pt_reference  : Place le point minimal en première position et crée le point de référence.
- calcul_coord_polaires: Calcule la distance et l'angle polaire de chaque point par rapport au point minimal.
- trier_pts            : Trie les points en ordre croissant d'angle polaire et de distance.
************************************************************************************/

//Permet de désactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS 

// Active les constantes mathématiques non standard de <math.h> (ex. M_PI)
#define _USE_MATH_DEFINES

#include <stdlib.h>     // Allocation dynamique, nombres aléatoires (malloc, free, rand)
#include <math.h>       // Fonctions mathématiques (sqrt, asin) et constante M_PI
#include "tab_points.h" // Type t_point et prototypes des fonctions de ce module
#include "affichage.h"  // Module d'affichage graphique des points et des lignes

/*==================================================================================*/
/*================================= FONCTIONS ======================================*/

/* SWAP */
void swap(t_point* a, t_point* b) {
    t_point tampon = *a;
    *a = *b;
    *b = tampon;
}

/*==================================================================================*/
/* VERIFIER_DOUBLONS */
int verifier_doublons(const t_point tab_pts[], int taille_actuelle, int y_aleatoire) {
    int j;
    
    // Parcourt le tableau de points pour vérifier si l'ordonnée (posy) 
    // de l'un d'eux est égale au y aléatoire. Si oui, c'est un doublon (retour 0).
    for (j = 0; j < taille_actuelle; j++) {
        if (tab_pts[j].posy == y_aleatoire) {
            return 0; 
        }
    }
    return 1; // Aucun doublon, le y est unique
}

/*==================================================================================*/
/* DISTANCE */
double distance(t_point * pA, t_point * pB){
    double diffx = pB->posx - pA->posx;
    double diffy = pB->posy - pA->posy;

    // Retourne la distance Euclidienne entre les points pA et pB.
    return sqrt((diffx *  diffx) + (diffy * diffy)); 
}

/*==================================================================================*/
/* PROD_VECTORIEL */
double prod_vectoriel(t_point * p0, t_point * p1, t_point * p2){
    // Calcul des différences de coordonnées par rapport au point d'origine p0 :
    // v2 = p2 - p0  ==>  a = x2 - x0,  c = y2 - y0
    // v1 = p1 - p0  ==>  b = x1 - x0,  d = y1 - y0
    double a = p2->posx - p0->posx;
    double b = p1->posx - p0->posx;
    double c = p2->posy - p0->posy;
    double d = p1->posy - p0->posy;

    // Calcul et retourne le produit vectoriel
    return (a*d) - (b*c);
}

/*==================================================================================*/
/* COORD_POLAIRE */
double coord_polaire(t_point * pA, t_point * pB, t_point * h_ref){
    // Calcul de la distance euclidienne entre pA et pB
    double dist = distance(pA, pB);

    // Calcul de l'angle polaire de base (en radians) avec asin() 
    double angle = asin((pB->posy - pA->posy) / dist);

    // Utilisation du point de référence h_ref pour déterminer si pB 
    // se trouve à gauche ou à droite de l'axe vertical passant par pA.
    // Le produit vectoriel (pA -> h_ref) x (pA -> pB) indique le signe de l'orientation.
    double produitVectoriel = prod_vectoriel(pA, h_ref, pB);

    if (produitVectoriel > 0.0) {
        // pB est à droite de l'axe de référence : l'angle de base est correct (aigu)
        return angle;
    } else if (produitVectoriel < 0.0) {
        // pB est à gauche de l'axe de référence : l'angle est obtus (> 90° ou > π/2).
        // On ajuste l'angle pour obtenir sa valeur obtuse équivalente.
        return angle + 2 *(M_PI/2 - angle);
    } else {
        return angle;
    }
}

/*==================================================================================*/
/* ALEA */ 
static int alea(int min, int max){    
    // Retourne un entier aléatoire dans [min, max]
	return (rand() % (max - min + 1) + min);
}

/*==================================================================================*/
/* INIT_TAB_ALEA */
void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy) {
    int i;
    int y_aleatoire;

    // Parcourt tout le tableau pour initialiser chaque point et
    // attribue une abscisse aléatoire comprise entre 1 et maxx
    for (i = 0; i < taille; i++) {
        tab_pts[i].posx = alea(1, maxx);

        // Répéter la génération tant que le y n'est pas unique
        do {
            y_aleatoire = alea(1, maxy);
        } while (verifier_doublons(tab_pts, i, y_aleatoire) == 0);

        tab_pts[i].posy = y_aleatoire;
    }
}

/*==================================================================================*/
/* TROUVER_PT_MINIMAL */
int trouver_pt_minimal(const t_point tab_pts[], int taille){
    int i;
    // Prendre la première valeur comme le min
    int indice = 0; 

    // Parcourt le tableau à partir du deuxième point
    for (i = 1; i < taille; i++)
        // Recherche de la plus petite ordonnée (posy)
        if (tab_pts[i].posy < tab_pts[indice].posy) 
        {
            indice = i;
        }
       // En cas d'égalité de posy, on choisit le point le plus à gauche (plus petit posx)
        else if (tab_pts[i].posy == tab_pts[indice].posy &&
                 tab_pts[i].posx < tab_pts[indice].posx) 
        {
            indice = i;
        }
   
	return indice;
}

/*==================================================================================*/
/* PLACER_PT_REFERENCE */
t_point placer_pt_reference(t_point tab_pts[], int pos_min){
    // Initialiser l'angle et la distance du point minimal a 0
    tab_pts[0].rad = 0;
    tab_pts[0].dist = 0;

    // Permuter le point minimal avec la case 0 du tableau 
    swap(&tab_pts[0], &tab_pts[pos_min]);    

    // Creer le point h_ref  (meme posx, posy = 800)
    t_point h_ref;
    h_ref.posx = tab_pts[0].posx;
    h_ref.posy = MAX_Y;     

    return h_ref;
}

/*==================================================================================*/
/* CALCUL_COORD_POLAIRES A TESTER*/
void calcul_coord_polaires(t_point tab_pts[], int taille, t_point* ref) {
    int i;

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

/*==================================================================================*/
/* TRIER_PTS */ 
void trier_pts(t_point tab_pts[], int taille)
{
    int i, j, indice;

    // On commence à 1 : le point en [0] reste à sa place
    for (i = 1; i < taille - 1; i++)
    {
        // On suppose que le i-ème point a le plus petit angle/distance
        indice = i;

        // Recherche du plus petit élément dans la partie non triée du tableau
        for (j = i + 1; j < taille; j++)
        {
            // Comparaison par ordre croissant des angles polaires (rad)
            // En cas d'égalité d'angle, on choisit celui avec la plus courte distance
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

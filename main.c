//programme-client qui utilise une structure de donnees "ordonnerPoints"
#define _CRT_SECURE_NO_WARNINGS 
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <ordonnerPoints.h>

/*=========================================================*/
/*================ PROGRAMME PRINCIPAL ====================*/
int main(void)
{
    // Declaration de variables de type t_point
    t_point tab_pts[TAILLE], h_ref;  
    // Declaration de la position du point minimal
	int pos_pt_min;     

    srand(time(NULL));    //initialise le générateur “rand()” 

    //Initialisation d'un tableau de points aleatoire avec init_tab_alea() de 
    init_tab_alea(tab_pts, TAILLE, 1400, 800); // maxx: 1400, maxy: 800

    trouver_pt_minimal(tab_pts, TAILLE);

    calcul_coord_polaires(tab_pts, TAILLE, &h_ref);

    // Calcule des coordonnees polaire et triage avec trier_pts()
    // href et initialiser dans la fonction 
    trier_pts(tab_pts, TAILLE);

	return 0;    
}
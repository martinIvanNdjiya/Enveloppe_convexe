/*=========================================================*/
//Permet de d�sactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 
#define _USE_MATH_DEFINES

// Librairies usuelles � inclure 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define TAILLE  20   

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/
typedef struct {        
	int posx, posy;   //coordonnées x, y du point dans le plan
    double rad;       //angle polaire relatif au point minimal
    double dist;      //la distance relative au point minimal
	int position;     //position-tableau du point suite au tri
} t_point;


double distance(t_point * pA, t_point * pB);

double prod_vectoriel(t_point * p0, t_point * p1, t_point * p2);

double coord_polaire(t_point * pA, t_point * pB, t_point * h_ref);

int alea(int min, int max);

void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy);

int  trouver_pt_minimal(const t_point tab_pts[], int taille);

t_point placer_pt_reference(t_point tab_pts[], int pos_min);

void calcul_coord_polaires(t_point tab_pts[], int taille, t_point * ref);

void trier_pts(t_point tab_pts[], int taille);


/*=========================================================*/
/*=========================================================*/
//Programme principal
int main(void)
{
    t_point tab_pts[TAILLE], h_ref;  
	int pos_pt_min;     

    srand(time(NULL));    //initialise le générateur “rand()” 

    init_tab_alea(tab_pts, TAILLE, 1400, 800);

    trouver_pt_minimal(tab_pts, pos_pt_min);

	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."	
	system("pause");
	return EXIT_SUCCESS;     //retour obligatoire si le "main()" est de type "int"
}

/*=========================================================*/

double distance(t_point * pA, t_point * pB){
    return sqrt (pow(pB->posx-pA->posx, 2) + pow(pB->posy - pA->posy, 2));
}

double prod_vectoriel(t_point * p0, t_point * p1, t_point * p2){
    double a = p1->posx - p0->posx;
    double b = p2->posx - p0->posx;
    double c = p1->posy - p0->posy;
    double d = p2->posy - p0->posy;

    return (a*d) - (b*c);
}

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

int alea(int min, int max){    
    //retourne un entier aléatoire dans [min, max]
	return (rand() % (max - min + 1) + min);
}

void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy){
    for (int i = 0; i < taille; i++) {

    }
}

int trouver_pt_minimal(const t_point tab_pts[], int taille){
    int j;
    int indice = 0;            //prendre premiere valeur comme etant le min

    for (j = 1; j < taille; j++)			 //pour toutes les autres valeurs
        if (tab_pts[j].posy < tab_pts[indice].posy) 
            indice = j;  

        else if (tab_pts[j].posy == tab_pts[indice].posy) {
            if (tab_pts[j].posx < tab_pts[indice].posx) {
                indice = j;
            }
        }
	return indice;
}

t_point placer_pt_reference(t_point tab_pts[], int pos_min){

}

void calcul_coord_polaires(t_point tab_pts[], int taille, t_point * ref){

}

void trier_pts(t_point tab_pts[], int taille){

}
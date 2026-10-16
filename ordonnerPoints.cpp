#define _CRT_SECURE_NO_WARNINGS 
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <ordonnerPoints.h>

/*=========================================================*/
/*=================== FONCTIONS ===========================*/
/* DISTANCE */
double distance(t_point * pA, t_point * pB){
    return sqrt (pow(pB->posx-pA->posx, 2) + pow(pB->posy - pA->posy, 2));
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
int alea(int min, int max){    
    //retourne un entier aléatoire dans [min, max]
	return (rand() % (max - min + 1) + min);
}

/* INIT_TAB_ALEA */
void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy) {
    int i, j; //compteurs
    int unique; // Int derterminant si la posy est unique 1 ou non 0
    int y_aleatoire; // y aleatoire 

    for (i = 0; i < taille; i++) {
        tab_pts[i].posx = alea(1, maxx);

        // Avoir une posy unique dans le tableau
        do {
            // Generation d'un y aleatoire avec alea()
            y_aleatoire = alea(1, maxy);

            // On supposee que le y est unique
            unique = 1;

            // Verification des doublons
            for (j = 0; j < i; j++) {
                if (tab_pts[j].posy == y_aleatoire) {
                    unique = 0; // Trouve un doublon donc ce n'est pas unique
                    break;
                }
            }
        } while (unique == 0);

        tab_pts[i].posy = y_aleatoire;
    }
}

/* TROUVER_PT_MINIMAL  A TESTER!! */
int trouver_pt_minimal(const t_point tab_pts[], int taille){
    int i; //compteur
    int indice = 0;            //prendre premiere valeur comme etant le min

    for (i = 1; i < taille; i++)			 //pour toutes les autres valeurs
        if (tab_pts[i].posy < tab_pts[indice].posy) 
            indice = i;  

        else if (tab_pts[i].posy == tab_pts[indice].posy) {
            if (tab_pts[i].posx < tab_pts[indice].posx) {
                indice = i;
            }
        }
	return indice;
}

/* PLACER_PT_REFERENCE A TESTER !*/
t_point placer_pt_reference(t_point tab_pts[], int pos_min){
    // Permuter le point minimal avec la case 0 du tableau
    t_point temp = tab_pts[0];
    tab_pts[0] = tab_pts[pos_min];
    tab_pts[pos_min] = temp;

    // Creer le point h_ref  (meme posx, posy = 800)
    t_point h_ref;
    h_ref.posx = tab_pts[0].posx;
    h_ref.posy = 800; 

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

/* TRIER_PTS A TESTER*/ 
void trier_pts(t_point tab_pts[], int taille) {
    int i, j;
    t_point tampon;

    //Crearion du point de ref horizontal (meme posx que le point minimal a [0], y = 800)
    t_point h_ref;
    h_ref.posx = tab_pts[0].posx;
    h_ref.posy = 800; 

    // Calcule des coordonnees polaires en passant l'adresse de h_ref
    calcul_coord_polaires(tab_pts, taille, &h_ref);

    // Trier les points 
    for (i = 1; i < taille - 1; i++) {
        for (j = 1; j < taille - i; j++) {

            // Condition de permutation : angle plus grand OU angle egal mais distance plus grande
            if ((tab_pts[j].rad > tab_pts[j + 1].rad) || (tab_pts[j].rad == tab_pts[j + 1].rad && tab_pts[j].dist > tab_pts[j + 1].dist)) {

                // Permuter les deux points
                tampon = tab_pts[j];
                tab_pts[j] = tab_pts[j + 1];
                tab_pts[j + 1] = tampon;
            }
        }
    }
}
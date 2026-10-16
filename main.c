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

#define TAILLE  20   

/*=========================================================*/
/*============== DECLARATION DES FONCTIONS ================*/

/** DISTANCE
* Calcule et retourne la distance Euclidienne entre les points pA et pB
* en deux dimensions, pour deux points A(x1, y1) et B(x2, y2).
*
* PARAMETRES: pA ---> Pointeur vers le premier point pA (t_point *)
*             pB ---> Pointeur vers le deuxième point pB (t_point *)
* RETOUR    : La distance Euclidienne entre les deux points (double)
 */
double distance(t_point * pA, t_point * pB);

/** PROD_VECTORIEL
* Retourne le produit vectoriel des deux vecteurs formés par v1 = p1 - p0
* et v2 = p2 - p0, calculé via le déterminant d'une matrice 2 x 2.
*
* PARAMETRES: p0 ---> Pointeur vers le point d'origine p0 (t_point *)
*             p1 ---> Pointeur vers le premier point p1 (t_point *)
*             p2 ---> Pointeur vers le deuxième point p2 (t_point *)
* RETOUR    : Le résultat du produit vectoriel (double)
 */
double prod_vectoriel(t_point * p0, t_point * p1, t_point * p2);

/** COORD_POLAIRE
* Reçoit deux points pA et pB ainsi qu'un point de référence gauche-droite h_ref.
* Calcule et retourne l'angle polaire du vecteur pA - pB relatif à l'axe horizontal,
* en utilisant asin() et le produit vectoriel pour gérer les angles aigus et obtus.
*
* PARAMETRES: pA    ---> Pointeur vers le premier point pA (t_point *)
*             pB    ---> Pointeur vers le deuxième point pB (t_point *)
*             h_ref ---> Pointeur vers le point de référence vertical h_ref (t_point *)
* RETOUR    : L'angle polaire calculé (double)
 */
double coord_polaire(t_point * pA, t_point * pB, t_point * h_ref);

/** ALEA
* Retourne un entier aléatoire compris dans l'intervalle fermé [min, max].
*
* PARAMETRES: min ---> La valeur minimale de l'intervalle (int)
*             max ---> La valeur maximale de l'intervalle (int)
* RETOUR    : Un entier aléatoire entre min et max inclus (int)
 */
int alea(int min, int max);

/** INIT_TAB_ALEA
* Initialise tous les points du tableau avec des coordonnées aléatoires
* comprises entre [1, maxx] pour le X et [1, maxy] pour le Y,
* en s'assurant qu'aucun point ne partage le même posy.
*
* PARAMETRES: tab_pts[] ---> Le tableau de points à initialiser (t_point [])
*             taille     ---> Le nombre d'éléments dans le tableau (int)
*             maxx       ---> La valeur maximale pour la coordonnée X (int)
*             maxy       ---> La valeur maximale pour la coordonnée Y (int)
* RETOUR    : Aucun (void)
 */
void init_tab_alea(t_point tab_pts[], int taille, int maxx, int maxy);

/** TROUVER_PT_MINIMAL
* Trouve et retourne l'indice du point minimal dans le tableau tab_pts[].
* Le point minimal est défini par la plus petite coordonnée posy. En cas
* d'égalité, on sélectionne le point avec la plus petite coordonnée posx (le plus à gauche).
*
* PARAMETRES: tab_pts[] ---> Le tableau de points à analyser (const t_point [])
*             taille     ---> Le nombre d'éléments dans le tableau (int)
* RETOUR    : L'indice du point minimal dans le tableau (int)
 */
int trouver_pt_minimal(const t_point tab_pts[], int taille);

/** PLACER_PT_REFERENCE
* Permute le point minimal (situé à l'indice pos_min) avec le point à l'indice [0] du tableau.
* Crée et retourne un nouveau point de référence horizontal dont la coordonnée posx est
* identique à celle du nouveau point [0] et dont la coordonnée posy est fixée à 800.
*
* PARAMETRES: tab_pts[] ---> Le tableau de points à modifier (t_point [])
*             pos_min    ---> L'indice du point minimal trouvé précédemment (int)
* RETOUR    : Le point de référence horizontal créé (t_point)
 */
t_point placer_pt_reference(t_point tab_pts[], int pos_min);

/** CALCUL_COORD_POLAIRES
* Calcule pour chaque point du tableau (à partir du deuxième, indice 1)
* son angle polaire (.rad) par rapport au point minimal (case [0])
* et sa distance (.dist) par rapport à ce même point minimal.
*
* PARAMETRES: tab_pts[] ---> Le tableau de points à mettre à jour (t_point [])
*             taille     ---> Le nombre d'éléments dans le tableau (int)
*             ref        ---> Pointeur vers le point de référence horizontal (t_point *)
* RETOUR    : Aucun (void)
 */
void calcul_coord_polaires(t_point tab_pts[], int taille, t_point * ref);

/** TRIER_PTS
* Trie les points du tableau en ordre croissant de leurs angles polaires (.rad),
* en laissant obligatoirement le point minimal à la case [0].
* En cas d'égalité d'angle, on place le point avec la plus courte distance (.dist) en premier.
*
* PARAMETRES: tab_pts[] ---> Le tableau de points à trier (t_point [])
*             taille     ---> Le nombre d'éléments dans le tableau (int)
* RETOUR    : Aucun (void)
 */
void trier_pts(t_point tab_pts[], int taille);


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

    trouver_pt_minimal(tab_pts, pos_pt_min);

    // Calcule des coordonnees polaire et triage avec trier_pts()
    // href et initialiser dans la fonction 
    trier_pts(tab_pts, TAILLE);

	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."	
	system("pause");
	return EXIT_SUCCESS;     //retour obligatoire si le "main()" est de type "int"
}

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
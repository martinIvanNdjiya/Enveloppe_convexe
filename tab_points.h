//Permet de d�sactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 
#define _USE_MATH_DEFINES

// Librairies usuelles � inclure 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/
typedef struct {        
	int posx, posy;   //coordonnées x, y du point dans le plan
    double rad;       //angle polaire relatif au point minimal
    double dist;      //la distance relative au point minimal
	int position;     //position-tableau du point suite au tri
} t_point;

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
static int alea(int min, int max);   //privée!!

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
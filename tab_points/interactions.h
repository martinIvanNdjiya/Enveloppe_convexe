#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "tab_points.h"

/** DEMANDER_MODE
 * On affiche un menu qui propose les deux choix de modes d’exécution;
 * 1) mode aléatoire à 20 points,
 * 2) mode à partir d’un fichier-texte.
 * Le choix de l’utilisateur doit être validé.
 * PARAMETRES: AUCUN (void)
 * RETOUR    : 1 (mode aleatoire) ou 2 (mode fichier-texte).
 */
int demander_mode(void);

/** CHOISIR_FICHIER
 * Permet de sélectionner un des fichiers .txt de points disponibles.
 * On demande et on saisit le nom d’un fichier .txt.
 * On tente ensuite d’ouvrir ce fichier en mode lecture.
 * PARAMETRES: Aucun (void)
 * RETOUR    : Le pointeur d'accès au fichier choisi (FILE *)
 */
FILE* choisir_fichier(void);

/** LIRE_POINTS
 * Lit tous les points du fichier et les retourne dans un tableau dynamique.
 */
t_point* lire_points(FILE* fichier, int* nb_pts);
/************************************************************************************
Par    : Martin Ivan Ndjiya et Judith Andrasko
Date   : 10 novembre 2026 

Ce module implémente les fonctions d'interaction avec l'utilisateur et de lecture des
données nécessaires pour obtenir les points de l'algorithme de l'enveloppe convexe.
On y retrouve les sous-programmes suivants :
- demander_mode   : Demande à l'utilisateur le mode d'exécution ('1' aléatoire à 20 points,
                    '2' à partir d'un fichier texte, '3' simulation) et retourne son choix.
- choisir_fichier : Demande le nom d'un fichier texte de points et l'ouvre en lecture.
                    Répète la demande tant que l'ouverture échoue.
- lire_points     : Lit le nombre de points puis leurs coordonnées (posx, posy) dans le
                    fichier, les stocke dans un tableau alloué dynamiquement (position
                    initialisée à -1) et ferme le fichier.
************************************************************************************/


//Permet de désactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>       // Entrées/sorties standard (printf, scanf, fopen, perror, getchar)
#include "tab_points.h"  // Type t_point utilisé pour le tableau de points lu dans le fichier

// Vide le tampon du clavier en lisant les caractères jusqu'à la fin de la ligne.
#define FFLUSH()   while (getchar() != '\n')

/*==================================================================================*/
/* DEMANDER_MODE */
int demander_mode(void) {
    char reponse;
    int r = 1; // Initialisation au mode aleatoire

    printf("\n=================================================================");
    printf("\n==================== MODE D'EXECUTION ===========================");
    do {
        printf("\nVeuillez choisir entre ces modes ('1' ou '2' ou '3'): ");
        printf("\n\t 1) Mode aleatoire a 20 points;\n\t 2) À partir d'un fichier texte.\n\t 3) Mode simulation\n");
        scanf("%c", &reponse);

        FFLUSH();
    } while (!((reponse == '1') || (reponse == '2') || (reponse == '3')));

    if (reponse == '2') {
        r = 2;
    }
    else if (reponse == '3') {
        r = 3;
    }

    return r;
}

/*==================================================================================*/
/* CHOISIR_FICHIER */
FILE* choisir_fichier(void) {
    char nom[100];      // Tableau de caractères pour stocker le nom du fichier
    FILE *fentree = NULL;  

    do {
        printf("\nVeuillez entrer le nom du fichier texte des points : ");
        scanf("%s", nom);
        FFLUSH();

        fentree = fopen(nom, "r");

        if (fentree == NULL) {
            perror("Detail de l'erreur fopen: ");
            printf("\nERREUR : Lecture du fichier impossible. Veuillez reessayer.\n");
        }

    } while (fentree == NULL);

    return fentree;
}

/*==================================================================================*/
/* LIRE_POINTS */
t_point* lire_points(FILE* fichier, int* nb_pts) {
    // Lire le nombre de points et le mettre dans *nb_pts
    if (fscanf(fichier, "%d", nb_pts) != 1) {
        return NULL;
    }

    // Allocation dynamique du tableau de *nb_pts points
    t_point* tab_pts = (t_point*)malloc((*nb_pts) * sizeof(t_point));
    if (tab_pts == NULL) {
        return NULL;
    }

    // Lire les coordonnées ligne par ligne et initialiser .position à -1
    for (int i = 0; i < *nb_pts; i++) {
        fscanf(fichier, "%d %d", &tab_pts[i].posx, &tab_pts[i].posy); 
        tab_pts[i].position = -1;
    }

    fclose(fichier);

    return tab_pts;
}
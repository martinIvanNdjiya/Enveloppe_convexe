#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tab_points.h"

#define FFLUSH()   while (getchar() != '\n')

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
        fscanf(fichier, "%d %d", &tab_pts[i].posx, &tab_pts[i].posy); // %d car posx et posy sont des int
        tab_pts[i].position = -1;
    }

    fclose(fichier);

    return tab_pts;
}
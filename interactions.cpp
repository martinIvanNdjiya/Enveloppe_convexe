#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tab_points.h"

#define FFLUSH()   while (getchar() != '\n')

/* DEMANDER_MODE */
int demander_mode(void) {
    char rep;
    int r = 1; // Initialisation au mode aleatoire

    printf("\n=================================================================");
    printf("\n==================== MODE D'EXECUTION ===========================");
    do {
        printf("\nVeuillez choisir entre ces modes ('1' ou '2'): ");
        printf("\n\t 1) Mode aleatoire a 20 points;\n\t 2) A partir d'un fichier texte.\n");
        scanf("%c", &rep);

        FFLUSH();
    } while (!((rep == '1') || (rep == '2')));

    if (rep == '2') {
        r = 2;
    }

    return r;
}

/* CHOISIR_FICHIER */
FILE* choisir_fichier(void) {
    char nom[100];      // Tableau de caractères pour stocker le nom du fichier
    FILE *fentree = NULL;      // Pointeur de fichier correct (avec l'étoile)

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
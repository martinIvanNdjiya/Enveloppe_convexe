/************************************************************************************
Par    : Martin Ivan Ndjiya et Judith Andrasko
Date   : 11 novembre 2026

Ce module contient le programme principal et l'algorithme du balayage de Graham qui
permet de trouver l'enveloppe convexe d'un ensemble de points. Selon le mode choisi,
les points sont générés aléatoirement, lus dans un fichier texte, ou le programme
exécute une simulation statistique sans affichage.
On y retrouve les sous-programmes suivants :
- afficher_pts_en_ordre : Dessine les points triés avec leur numéro de position et,
                          au besoin, les vecteurs polaires depuis le point de référence.
- algo_Graham_scan      : Applique l'algorithme de Graham sur des points triés par angle
                          polaire et conserve les points de l'enveloppe dans une pile.
                          Retourne le nombre de points de l'enveloppe.
- afficher_segments     : Affiche le nombre et les coordonnées des points de l'enveloppe
                          puis dessine les segments qui la ferment (vide la pile).
- simulation_moyenne    : Calcule le nombre moyen de points dans l'enveloppe convexe
                          pour un nombre d'essais de tableaux de points aléatoires.
- main                  : Gère les trois modes d'exécution (aléatoire, fichier,
                          simulation), prépare et trie les points, puis affiche
                          l'enveloppe convexe.
************************************************************************************/

#include "tab_points.h"     // Type t_point et prototypes des fonctions de ce module
#include "affichage.h"      // Module d'affichage graphique 
#include "PILESLIB.H"       // Type t_pile et opérations de la pile 
#include <assert.h>         // Macro assert() pour valider les allocations et l'ouverture de fichiers
#include "interactions.h"   // Fonctions de saisie 

#define TAILLE  20          // Nombre de points générés en mode aléatoire
#define MODE_ALEA 1         // Mode 1 : points générés aléatoirement
#define MODE_FICHIER 2      // Mode 2 : points lus à partir d'un fichier texte
#define MODE_SIMULATION 3   // Mode 3 : simulation statistique sans affichage graphique
#define NB_ESSAIS 10000     // Nombre d'essais par taille de tableau en mode simulation

/******************************************************************************/
/*
 * afficher_pts_en_ordre : dessine tous les points du tableau (déjà triés)
 * avec leur numéro de position.
 * Paramètres :
 *   tab_pts : tableau de points triés;
 *   taille  : nombre de points dans le tableau;
 *   ligne   : si non nul, trace aussi une ligne entre le point de
 *             référence (tab_pts[0]) et chacun des autres points.
 */
void afficher_pts_en_ordre(t_point tab_pts[], int taille, int ligne);

/******************************************************************************/
/*
 * algo_Graham_scan : applique l'algorithme de Graham sur un tableau de points
 * déjà trié selon l'angle polaire autour du point de référence (tab_pts[0]).
 * Les points de l'enveloppe convexe sont conservés dans la pile.
 * Paramètres :
 *   tab_pts    : tableau de points triés;
 *   nb_pts     : nombre de points dans le tableau;
 *   pile_Graham: pile (déjà initialisée) qui contiendra l'enveloppe;
 *   mode_aff   : si non nul, affiche graphiquement chaque étape.
 * Retour : le nombre de points dans l'enveloppe convexe.
 */
int  algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile *pile_Graham, int mode_aff);

/******************************************************************************/
/*
 * afficher_segments : affiche à l'écran le nombre de points de l'enveloppe
 * et leurs coordonnées, puis dessine les segments qui ferment l'enveloppe.
 * La pile est vidée pendant le parcours.
 * Paramètre :
 *   pile_Graham : pile contenant les points de l'enveloppe convexe.
 */
void afficher_segments(t_pile *pile_Graham);

/**********************************************************************************/
/*
 * simulation_moyenne : calcule le nombre moyen de points dans l'enveloppe
 * convexe pour des tableaux de points aléatoires.
 * Paramètres :
 *   nb_pts   : nombre de points générés à chaque essai;
 *   nb_tests : nombre d'essais à effectuer.
 * Retour : la moyenne de points dans l'enveloppe sur l'ensemble des essais.
 */
double simulation_moyenne(int nb_pts, int nb_tests);

/*================ PROGRAMME PRINCIPAL ====================*/ 
int main(void)
{
    t_point* tab_pts = NULL;    // Tableau dynamique des points
    t_point h_ref;              // Point de référence (le plus bas)
    t_pile pile_Graham;         // Pile contenant les points de l'enveloppe
    FILE* f_log = NULL;         // Fichier de résultats de la simulation

    int nb_pts = 0;             // Nombre de points dans le tableau
    int pos_pt_min;             // Position du point minimal dans le tableau
    int mode;                   // Mode choisi par l'utilisateur

    mode = demander_mode();

    // MODE_ALEA
    if (mode == MODE_ALEA) {
        nb_pts = TAILLE;
        tab_pts = (t_point*)malloc(nb_pts * sizeof(t_point));
        assert(tab_pts != NULL);
        init_tab_alea(tab_pts, nb_pts, MAX_X, MAX_Y);
    }
    // MODE_FICHIER
    else if (mode == MODE_FICHIER) {
        FILE* fichier = choisir_fichier();
        tab_pts = lire_points(fichier, &nb_pts);
        assert(tab_pts != NULL);
    }
    // MODE_SIMULATION
    else {
        f_log = fopen("log_simulation.txt", "w");
        assert(f_log != NULL);

        // Pour chaque taille de 5 à 200 points (par bonds de 5), on simule 10000 essais
        for (nb_pts = 5; nb_pts <= 200; nb_pts += 5) {
            double moy = simulation_moyenne(nb_pts, NB_ESSAIS);
            printf("%d  %.2f\n", nb_pts, moy);
            fprintf(f_log, "%d  %.2f\n", nb_pts, moy);
        }

        fclose(f_log);
        return 0;  
    }

    // Modes 1 et 2 : préparation des points
    pos_pt_min = trouver_pt_minimal(tab_pts, nb_pts);
    h_ref = placer_pt_reference(tab_pts, pos_pt_min);

    calcul_coord_polaires(tab_pts, nb_pts, &h_ref);
    trier_pts(tab_pts, nb_pts);

    // Affichage des points triés avec les vecteurs polaires
    mode_graphique();
    afficher_pts_en_ordre(tab_pts, nb_pts, 1);
    pause_ecran();

    // Redessiner sans les vecteurs, puis parcours de Graham avec affichage
    nettoyer_ecran();
    afficher_pts_en_ordre(tab_pts, nb_pts, 0);
    pile_Graham = init_pile(nb_pts);
    algo_Graham_scan(tab_pts, nb_pts, &pile_Graham, 1);
    afficher_segments(&pile_Graham);
    pause_ecran();

    fermer_mode_graph();
    liberer_pile(&pile_Graham);
    free(tab_pts);
    return 0;
}

/******************************************************************************/
void afficher_pts_en_ordre(t_point tab_pts[], int taille, int ligne) {
    // Pour chaque point du tableau
    for (int i = 0; i < taille; i++) {
        tab_pts[i].position = i;
        dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, tab_pts[i].position);

        // Si demandé, on relie le point de référence au point courant
        if (ligne) {
            dessiner_lig(tab_pts[0].posx, tab_pts[0].posy,
                         tab_pts[i].posx, tab_pts[i].posy);
        }    
    }
}

/******************************************************************************/
int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile* pile_Graham, int mode_aff) {
    t_point p0 = tab_pts[0];
    t_point p1 = tab_pts[1];
    t_point p2 = tab_pts[2];

    // Les trois premiers points sont empilés au départ
    push(pile_Graham, p0);
    push(pile_Graham, p1);
    push(pile_Graham, p2);

    // Si l'affichage est activé, on dessine les deux premiers segments
    if (mode_aff) {
        dessiner_lig(p0.posx, p0.posy, p1.posx, p1.posy);
        dessiner_lig(p1.posx, p1.posy, p2.posx, p2.posy);
        delai_ecran(300);
    }

    // Pour chacun des points restants (à partir du 4e)
    for (int i = 3; i < nb_pts; i++) {
        t_point pA, pB;             // pB = sommet de la pile, pA = point sous le sommet
        t_point pi = tab_pts[i];    // Point courant à tester

        // On dépile tant que le virage n'est pas dans le bon sens
        do {
            get_sommet(pile_Graham, &pB);
            get_suiv_sommet(pile_Graham, &pA);

            // Si le produit vectoriel est positif, pB est à l'intérieur : on le retire
            if (prod_vectoriel(&pA, &pB, &pi) > 0) {
                pop(pile_Graham, &pB);
                // Si l'affichage est activé, on efface le segment retiré
                if (mode_aff) {
                    effacer_lig(pA.posx, pA.posy, pB.posx, pB.posy);
                    delai_ecran(100);
                }
            }
        } while (prod_vectoriel(&pA, &pB, &pi) > 0);

        // Le point courant fait (provisoirement) partie de l'enveloppe
        push(pile_Graham, pi);

        // Si l'affichage est activé, on trace le nouveau segment
        if (mode_aff) {
            dessiner_lig(pB.posx, pB.posy, pi.posx, pi.posy);
            delai_ecran(300);
        }
    }

    return get_nb_elements(pile_Graham);
}

/******************************************************************************/
void afficher_segments(t_pile* pile_Graham) {
    t_point p0, p1, pt_fin;

    printf("%d Points dans l'enveloppe\n", get_nb_elements(pile_Graham));

    // Le premier point dépilé sert aussi de point final pour fermer l'enveloppe
    pop(pile_Graham, &pt_fin);
    printf("(%d, %d)\n", pt_fin.posx, pt_fin.posy);
    p0 = pt_fin;

    // Tant qu'il reste des points dans la pile, on dessine le segment suivant
    while (!vide(pile_Graham)) {
        pop(pile_Graham, &p1);
        dessiner_lig(p0.posx, p0.posy, p1.posx, p1.posy);
        printf("(%d, %d)\n", p1.posx, p1.posy);
        p0 = p1;
    }

    // Dernier segment : on referme l'enveloppe
    dessiner_lig(p0.posx, p0.posy, pt_fin.posx, pt_fin.posy);
}

/**********************************************************************************/
double simulation_moyenne(int nb_pts, int nb_tests) {
    t_pile pile_Graham;
    t_point* tab_pts = NULL;
    t_point h_ref = { 0 };
    int p_min;
    int nb_pts_tot = 0;     // Somme des points d'enveloppe de tous les essais

    tab_pts = (t_point*)malloc(nb_pts * sizeof(t_point));
    assert(tab_pts != NULL);

    // Pour chaque essai de la simulation
    for (int i = 0; i < nb_tests; i++) {
        pile_Graham = init_pile(nb_pts);
        init_tab_alea(tab_pts, nb_pts, MAX_X, MAX_Y);

        p_min = trouver_pt_minimal(tab_pts, nb_pts);
        h_ref = placer_pt_reference(tab_pts, p_min);

        calcul_coord_polaires(tab_pts, nb_pts, &h_ref);
        trier_pts(tab_pts, nb_pts);

        // Graham scan sans affichage; on cumule la taille de l'enveloppe
        nb_pts_tot += algo_Graham_scan(tab_pts, nb_pts, &pile_Graham, 0);

        liberer_pile(&pile_Graham);
    }

    free(tab_pts);
    return (double) nb_pts_tot / nb_tests;
}
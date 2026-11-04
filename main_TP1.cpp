#include "tab_points.h"
#include "affichage.h"
#include "PILESLIB.H"
#include <assert.h>
#include "interactions.h"

#define TAILLE  20 
#define MODE_ALEA 1
#define MODE_FICHIER 2
#define MODE_SIMULATION 3
#define NB_ESSAIS 10000

void afficher_pts_en_ordre(t_point tab_pts[], int taille, int ligne);
int  algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile *pile_Graham, int mode_aff);
void afficher_segments(t_pile *pile_Graham);
double simulation_moyenne(int nb_pts, int nb_tests);

/*================ PROGRAMME PRINCIPAL ====================*/ 
int main(void)
{
    t_point* tab_pts = NULL;
    t_point h_ref;
    t_pile pile_Graham;
    FILE* f_log = NULL;

    int nb_pts = 0;
    int pos_pt_min;
    int mode;

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
    for (int i = 0; i < taille; i++) {
        tab_pts[i].position = i;
        dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, tab_pts[i].position);
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

    push(pile_Graham, p0);
    push(pile_Graham, p1);
    push(pile_Graham, p2);

    if (mode_aff) {
        dessiner_lig(p0.posx, p0.posy, p1.posx, p1.posy);
        dessiner_lig(p1.posx, p1.posy, p2.posx, p2.posy);
        delai_ecran(300);
    }

    for (int i = 3; i < nb_pts; i++) {
        t_point pA, pB;
        t_point pi = tab_pts[i];

        do {
            get_sommet(pile_Graham, &pB);
            get_suiv_sommet(pile_Graham, &pA);

            if (prod_vectoriel(&pA, &pB, &pi) > 0) {
                pop(pile_Graham, &pB);
                if (mode_aff) {
                    effacer_lig(pA.posx, pA.posy, pB.posx, pB.posy);
                    delai_ecran(100);
                }
            }
        } while (prod_vectoriel(&pA, &pB, &pi) > 0);

        push(pile_Graham, pi);

        if (mode_aff) {
            dessiner_lig(pB.posx, pB.posy, pi.posx, pi.posy);
            delai_ecran(300);
        }
    }

    return get_nb_elements(pile_Graham);
}

/******************************************************************************/
void afficher_segments(t_pile *pile_Graham) {
    t_point p0, p1, pt_fin;

    printf("%d Points dans l'enveloppe\n", get_nb_elements(pile_Graham));

    pop(pile_Graham, &pt_fin);
    printf("(%d, %d)\n", pt_fin.posx, pt_fin.posy);
    p0 = pt_fin;

    while (!vide(pile_Graham)) {
        pop(pile_Graham, &p1);
        dessiner_lig(p0.posx, p0.posy, p1.posx, p1.posy);
        printf("(%d, %d)\n", p1.posx, p1.posy);
        p0 = p1;
    }

    dessiner_lig(p0.posx, p0.posy, pt_fin.posx, pt_fin.posy);
}

/**********************************************************************************/
double simulation_moyenne(int nb_pts, int nb_tests) {
    t_pile pile_Graham;
    t_point* tab_pts = NULL;
    t_point h_ref = { 0 };
    int p_min;
    int nb_pts_tot = 0;

    tab_pts = (t_point*)malloc(nb_pts * sizeof(t_point));
    assert(tab_pts != NULL);

    for (int i = 0; i < nb_tests; i++) {
        pile_Graham = init_pile(nb_pts);
        init_tab_alea(tab_pts, nb_pts, MAX_X, MAX_Y);

        p_min = trouver_pt_minimal(tab_pts, nb_pts);
        h_ref = placer_pt_reference(tab_pts, p_min);

        calcul_coord_polaires(tab_pts, nb_pts, &h_ref);
        trier_pts(tab_pts, nb_pts);

        nb_pts_tot += algo_Graham_scan(tab_pts, nb_pts, &pile_Graham, 0);

        liberer_pile(&pile_Graham);
    }

    free(tab_pts);
    return (double)nb_pts_tot / nb_tests;
}
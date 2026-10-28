#include "tab_points.h"
#include "affichage.h"
#include "PILESLIB.H"
#include <assert.h>

#define TAILLE  20 

void afficher_pts_en_ordre(t_point tab_pts[], int taille, int ligne);
int  algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile *pile_Graham);
void afficher_segments(t_pile *pile_Graham);

/*================ PROGRAMME PRINCIPAL ====================*/ 
int main(void)
{
    t_point* tab_pts = NULL;
    t_point h_ref;
    t_pile pile_Graham;
    int pos_pt_min;

    tab_pts = (t_point*)malloc(TAILLE * sizeof(t_point));
    assert(tab_pts != NULL);
   
    srand(time(NULL));

    init_tab_alea(tab_pts, TAILLE, MAX_X, MAX_Y);

    pos_pt_min = trouver_pt_minimal(tab_pts, TAILLE);
    h_ref = placer_pt_reference(tab_pts, pos_pt_min);

    calcul_coord_polaires(tab_pts, TAILLE, &h_ref);
    // trier_pts() recalcule les coordonnées polaires;
    // garde un seul des deux appels
    trier_pts(tab_pts, TAILLE);

    mode_graphique();
    afficher_pts_en_ordre(tab_pts, TAILLE, 1);
    pause_ecran();
    
    nettoyer_ecran();                              
    afficher_pts_en_ordre(tab_pts, TAILLE, 0);   
    pile_Graham = init_pile(TAILLE);               
    algo_Graham_scan(tab_pts, TAILLE, &pile_Graham); 
    afficher_segments(&pile_Graham);               
    pause_ecran();

    fermer_mode_graph();    
    liberer_pile(&pile_Graham);
    free(tab_pts);
    return 0;
}

//
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

//
int algo_Graham_scan(t_point tab_pts[], int nb_pts, t_pile *pile_Graham){
    *pile_Graham = init_pile(nb_pts);

    t_point p0 = tab_pts[0];
    t_point p1 = tab_pts[1];
    t_point p2 = tab_pts[2];

    push(pile_Graham, p0);
    push(pile_Graham, p1);
    push(pile_Graham, p2);

    dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, tab_pts[1].posx, tab_pts[1].posy);
    dessiner_lig(tab_pts[1].posx, tab_pts[1].posy, tab_pts[2].posx, tab_pts[2].posy);
    delai_ecran(300);

    for (int i = 3; i <= nb_pts-1; i++){
        // Déclaration des variables
        t_point pB;
        t_point pA;
        t_point pi = tab_pts[i];

        do {
            get_sommet(pile_Graham, &pB);
            get_suiv_sommet(pile_Graham, &pA);

            if (prod_vectoriel(&pA, &pB, &pi) > 0){
                pop(pile_Graham, &pB);
                effacer_lig(pA.posx, pA.posy, pB.posx, pB.posy);
                delai_ecran(100);
            }
        } 
        while (prod_vectoriel(&pA, &pB, &pi) > 0);

        push(pile_Graham, tab_pts[i]);
        dessiner_lig(pB.posx, pB.posy, pi.posx, pi.posy);
        delai_ecran(300);
    }

    return get_nb_elements(pile_Graham);
}

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
#include "tab_points.h"
#include "affichage.h"
#include <assert.h>

#define TAILLE  20   //dans le main()

/*================ PROGRAMME PRINCIPAL ====================*/ 
int main(void)
{
    t_point* tab_pts = NULL;
    tab_pts = (t_point*)malloc(TAILLE * sizeof(t_point));
    t_point h_ref;

    assert(tab_pts != NULL);
    int pos_pt_min;

    srand(time(NULL));

    init_tab_alea(tab_pts, TAILLE, MAX_X, MAX_Y);

    pos_pt_min = trouver_pt_minimal(tab_pts, TAILLE);
    h_ref = placer_pt_reference(tab_pts, pos_pt_min);

    calcul_coord_polaires(tab_pts, TAILLE, &h_ref);
    // trier_pts() recalcule les coordonnées polaires;
    // garde un seul des deux appels
    trier_pts(tab_pts, TAILLE);
    mode_graphique();
    afficher_pts_en_ordre(tab_pts, TAILLE);
    fermer_mode_graph();

    free(tab_pts);

    return 0;
}

//
void afficher_pts_en_ordre(t_point tab_pts[], int taille) {
    for (int i = 0; i < taille; i++) {
        tab_pts[i].position = i;
        dessiner_pt(tab_pts[i].posx, tab_pts[i].posy, tab_pts[i].position);
        dessiner_lig(tab_pts[0].posx, tab_pts[0].posy, tab_pts[i].posx, tab_pts[i].posy);
    }
}


t_pile init_pile(int taille) {

}
void liberer_pile(t_pile* pile) {

}
int get_sommet(const t_pile* pile, t_element* elem);
int get_suiv_sommet(const t_pile* pile, t_element* elem);
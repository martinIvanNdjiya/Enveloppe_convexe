#include "tab_points.h"
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

    init_tab_alea(tab_pts, TAILLE, 1400, 800);

    pos_pt_min = trouver_pt_minimal(tab_pts, TAILLE);
    h_ref = placer_pt_reference(tab_pts, pos_pt_min);

    calcul_coord_polaires(tab_pts, TAILLE, &h_ref);
    // trier_pts() recalcule les coordonnées polaires;
    // garde un seul des deux appels
    trier_pts(tab_pts, TAILLE);

    free(tab_pts);

    return 0;
}
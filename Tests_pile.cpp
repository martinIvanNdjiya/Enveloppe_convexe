/********************************************************************************/
/* Tests_pile.cpp: programme de tests unitaires de la pile de points (t_point). */
/* Auteur: Eric Th�, A26.                                                       */
/********************************************************************************/
//Permet de d�sactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 
// Librairies usuelles � inclure 
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>   //pour faire des tests unitaires avec "assert()"
#include<time.h>
#include "PILESLIB.h"

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/
#define TAILLE     10    //taille de la pile pour les tests

/********************************************************************************/
/* Programme principal : fonction principale qui retourne un entier (int)       */
/********************************************************************************/
int main(void) {
	t_point pt = {0}, ptA, ptB;    //variables pour ajouter/retirer des points de la pile
	t_pile  pile;				   //la pile de points � tester

	pile = init_pile(TAILLE);	   //cr�er une pile de 10 pts.

	//remplir la pile avec les points (1, -1), (2, -2), (3, -3), etc.
	//jusqu'� ce qu'elle soit pleine
	while (get_nb_elements(&pile) < TAILLE) {
		pt.posx += 1;      //1, 2, 3, 4, etc.
		pt.posy -= 1;	   //-1, -2, -3, -4, etc.

		push(&pile, pt);   //empiler (push) le point pt
	}
	//valider le nb. de points (= 10) et la position du sommet
	assert(get_nb_elements(&pile) == TAILLE);
	assert(pile.sommet == TAILLE - 1);
	printf("La pile contient %d elements.\n", get_nb_elements(&pile));

	//obtenir une copie du point-sommet
	if (get_sommet(&pile, &ptA))
	    printf("Le point qui se trouve au sommet est (%d, %d)\n", ptA.posx, ptA.posy);

	//obtenir une copie du point suivant du sommet
	if (get_suiv_sommet(&pile, &ptB))
	    printf("Le point suivant du sommet est (%d, %d)\n\n", ptB.posx, ptB.posy);

	//faire 5 fois des pop()
	for (int i = 1; i <= 5; i++) {    
		pop(&pile, &pt);
		printf("Le point (%2d, %3d) a ete retire de la pile\n", pt.posx, pt.posy);
	}
	//valider le nb. de points (= 5) et la position du sommet
	assert(get_nb_elements(&pile) == 5);
	assert(pile.sommet == 4);
	printf("La pile contient %d elements.\n", get_nb_elements(&pile));

	//si possible, obtenir une copie du point-sommet
	if (get_sommet(&pile, &ptA))
	    printf("Le point qui se trouve au sommet est (%d, %d)\n", ptA.posx, ptA.posy);
	//si possible, obtenir une copie du point suivant du sommet
	if (get_suiv_sommet(&pile, &ptB))
	    printf("Le point suivant du sommet est (%d, %d)\n\n", ptB.posx, ptB.posy);

	//faire 4 autres pop()
	for (int i = 1; i <= 4; i++) {    
		pop(&pile, &pt);
		printf("Le point (%2d, %3d) a ete retire de la pile\n", pt.posx, pt.posy);
	}
	//valider le nb. de points (= 1) et la position du sommet
	assert(get_nb_elements(&pile) == 1);
	assert(pile.sommet == 0);

	//si possible, obtenir une copie du point-sommet
	if (get_sommet(&pile, &ptA))
		 printf("Le point qui se trouve au sommet est (%d, %d)\n", ptA.posx, ptA.posy);
	else printf("La pile est vide!\n");

	//si possible, obtenir une copie du point suivant du sommet
	if (get_suiv_sommet(&pile, &ptB))
		 printf("Le point suivant du sommet est (%d, %d)\n\n", ptB.posx, ptB.posy);
	else printf("Pas assez d'elements dans la pile!\n");

	//on retire (pop) de dernier �l�ment de la pile
	pop(&pile, &pt);
	printf("Le point (%2d, %3d) a ete retire de la pile\n", pt.posx, pt.posy);
	//valider le nb. de points (= 0) et la position du sommet (= -1)
	assert(get_nb_elements(&pile) == 0);
	assert(pile.sommet == -1);

	//si possible, obtenir une copie du point-sommet
	if (get_sommet(&pile, &ptA))
		 printf("Le point qui se trouve au sommet est (%d, %d)\n", ptA.posx, ptA.posy);
	else printf("La pile est vide!\n");

	//lib�rer le tableau dynamique de la pile 
	liberer_pile(&pile);
	assert(pile.items == NULL);   //le pointeur-tableau doit avoir �t� remis � NULL

	printf("\nTous les tests ont reussi!\n");
	return EXIT_SUCCESS;
}

/********************************************************************************/
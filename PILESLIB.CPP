/************************************************************************************
Par    : Martin Ivan Ndjiya et Judith Andrasko
Date   : 10 novembre 2026
pileslib
Ce module implémente une pile dynamique de points (t_pile) utilisée par l'algorithme
de Graham pour conserver les points de l'enveloppe convexe. Les éléments sont stockés
dans un tableau alloué dynamiquement, dont la taille maximale est fixée à la création.
On y retrouve les sous-programmes suivants :
- init_pile       : Crée une pile vide pouvant contenir au maximum 'taille' éléments.
- liberer_pile    : Libère le tableau dynamique de la pile et la remet à zéro.
- vide            : Vérifie si la pile est vide.
- pleine          : Vérifie si la pile est pleine.
- push            : Empile un élément au sommet de la pile (erreur si pleine).
- pop             : Dépile l'élément au sommet de la pile (erreur si vide).
- get_nb_elements : Retourne le nombre d'éléments présents dans la pile.
- get_sommet      : Copie l'élément au sommet sans le retirer de la pile.
                    Retourne 1 en cas de succès, 0 si la pile est vide.
- get_suiv_sommet : Copie l'élément situé juste sous le sommet sans modifier la pile.
                    Retourne 1 en cas de succès, 0 s'il y a moins de deux éléments.
************************************************************************************/

//Permet de désactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>      // Entrées/sorties standard (printf pour les messages d'erreur)
#include "pileslib.h"   // Type t_pile, t_element et prototypes des fonctions de la pile

/*==================================================================================*/
/*================================= FONCTIONS ======================================*/

/*==================================================================================*/
/* INIT_PILE */
t_pile init_pile(int taille){ 
    t_pile pile;
    
    // Allocation dynamique du tableau d'éléments
    pile.items = (t_element *)malloc(taille * sizeof(t_element));
    
    // Vérification si l'allocation a réussi
    if (pile.items == NULL) {
        printf("Erreur : Allocation mémoire échouée pour la pile.\n");
        exit(1); 
    }
    
    // Initialisation des propriétés de la pile
    pile.sommet = -1;      // La pile est vide au départ
    pile.taille = taille;  // Stockage de la taille maximale
    
    return pile; // Retourne une copie de la pile ainsi créée
}

/*==================================================================================*/
/* LIBERER_PILE */
void liberer_pile(t_pile * pile){
    if (pile == NULL) {
      exit(EXIT_FAILURE); 
    }

    free(pile->items);   // on libère le tableau dynamique
    pile->items = NULL;
    pile->sommet = -1;
    pile->taille = 0;
}

/*==================================================================================*/
/* VIDE */
int vide(const t_pile *pile) {
  return (pile->sommet == -1); 
}

/*==================================================================================*/
/* PLEINE */
int  pleine(const t_pile *pile)
{ return (pile->sommet == pile->taille-1); }

/*==================================================================================*/
/* PUSH */
void push(t_pile *p, t_element el) { 
  if (pleine(p)) { 
    printf("ERREUR!!! Debordement de pile."); 
  }
  else {
    p->sommet++;
    p->items[p->sommet] = el;
  }
}

/*==================================================================================*/
/* POP */
void pop(t_pile *p, t_element *el) { 
  if (vide(p)) { 
	  printf("ERREUR!!! Pile vide."); 
  }
  else {
    *el = p->items[p->sommet];
    p->sommet--;
  }
}

/*==================================================================================*/
/* GET_NB_ELEMENTS */
int get_nb_elements(const t_pile * pile) {
  return pile->sommet + 1;
}

/*==================================================================================*/
/* GET_SOMMET */
int get_sommet(const t_pile * pile, t_element * elem) {
  if (vide(pile)) { 
    return 0;
  }
  else { 
    *elem = pile->items[pile->sommet];
    return 1;
  }
}

/*==================================================================================*/
/* GET_SUIV_SOMMET */
int get_suiv_sommet(const t_pile * pile, t_element * elem) {
  if (pile->sommet < 1) {
    return 0;
  }
  else {
    *elem = pile->items[pile->sommet - 1];
    return 1;
  }
}
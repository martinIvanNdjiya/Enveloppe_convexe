#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "pileslib.h"

//proc�dure pour initializer une pile, la pile sera vide 
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
 
//fonction pour nettoyer une pile 
void liberer_pile(t_pile * pile){
    if (pile == NULL) {
      exit(EXIT_FAILURE); 
    }

    free(pile->items);   // on libère le tableau dynamique
    pile->items = NULL;
    pile->sommet = -1;
    pile->taille = 0;
}

//fonction pour v�rifier si une pile est vide
int vide(const t_pile *pile) {
  return (pile->sommet == -1); 
}

//fonction pour v�rifier si une pile est pleine
int  pleine(const t_pile *pile)
{ return (pile->sommet == pile->taille-1); }

//proc�dure pour ajouter un �l�ment de plus sur une pile
void push(t_pile *p, t_element el) { 
  if (pleine(p)) { 
    printf("ERREUR!!! Debordement de pile."); 
  }
  else {
    p->sommet++;
    p->items[p->sommet] = el;
  }
}

//proc�dure pour enlever un �l�ment du haut d'une pile
void pop(t_pile *p, t_element *el) { 
  if (vide(p)) { 
	  printf("ERREUR!!! Pile vide."); 
  }
  else {
    *el = p->items[p->sommet];
    p->sommet--;
  }
}

int get_nb_elements(const t_pile * pile) {
  return pile->sommet + 1;
}

int get_sommet(const t_pile * pile, t_element * elem) {
  if (vide(pile)) { 
    return 0;
  }
  else { 
    *elem = pile->items[pile->sommet];
    return 1;
  }
}

int get_suiv_sommet(const t_pile * pile, t_element * elem) {
  if (pile->sommet < 1) {
    return 0;
  }
  else {
    *elem = pile->items[pile->sommet - 1];
    return 1;
  }
}
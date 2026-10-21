#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "pileslib.h"

//proc�dure pour initializer une pile, la pile sera vide 
t_pile init_pile(int taille){ 
    t_pile p;
    
    // Allocation dynamique du tableau d'éléments
    p.items = (t_element *)malloc(taille * sizeof(t_element));
    
    // Vérification si l'allocation a réussi
    if (p.items == NULL) {
        printf("Erreur : Allocation mémoire échouée pour la pile.\n");
        exit(EXIT_FAILURE); 
    }
    
    // Initialisation des propriétés de la pile
    p.sommet = -1;      // La pile est vide au départ
    p.taille = taille;  // Stockage de la taille maximale
    
    return p; // Retourne une copie de la pile ainsi créée
}

//fonction pour nettoyer une pile 
void liberer_pile(t_pile * pile){

}

//fonction pour v�rifier si une pile est vide
int  vide(const t_pile *p)
{ return (p->sommet == -1); }

//proc�dure pour ajouter un �l�ment de plus sur une pile
void push(t_pile *p, t_element el)
{ 
  if (pleine(p)) { 
    printf("ERREUR!!! Debordement de pile."); 
  }
  else {
    p->sommet++;
    p->items[p->sommet] = el;
  }
}

//proc�dure pour enlever un �l�ment du haut d'une pile
void pop(t_pile *p, t_element *el)
{ 
  if (vide(p)) { 
	  printf("ERREUR!!! Pile vide."); 
  }
  else {
    *el = p->items[p->sommet];
    p->sommet--;
  }
}


int get_sommet(const t_pile * pile, t_element * elem){}

int get_suiv_sommet(const t_pile * pile, t_element * elem){}
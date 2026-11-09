// Évite d'inclure ce fichier d'en-tête plus d'une fois lors de la compilation
#pragma once

//Permet de désactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS 

// Active les constantes mathématiques non standard de <math.h> 
#define _USE_MATH_DEFINES

#include<stdio.h>    // Entrées/sorties standard 
#include<stdlib.h>   // Allocation dynamique et nombres aléatoires 
#include<math.h>     // Fonctions mathématiques 
#include<time.h>     // Fonctions liées au temps 

#include "tab_points.h"  // Type t_point, utilisé pour définir le type t_element de la pile

//changer cette d�claration pour obtenir une pile pour un autre type
typedef t_point t_element;

typedef struct {
	t_element * items;	  //tableau dynamique des éléments de la pile
	int sommet;			  //position du sommet (top) de la pile, sera == -1 lorsque vide 
	int taille;			  //taille maximale du tableau dynamique des éléments
} t_pile;

/*Proc�dure pour initialiser une pile, la pile sera vide apr�s un appel
	de cette proc�dure. Peut aussi �tre utilis�e pour vider une pile. */
t_pile init_pile(int taille);

//fonction pour v�rifier si une pile est pleine
int pleine(const t_pile *);

//fonction pour v�rifier si une pile est vide
int vide(const t_pile *);

//fonction pour nettoyer une pile 
void liberer_pile(t_pile * pile);

//proc�dure pour ajouter un �l�ment de plus sur une pile
void push(t_pile *, t_element);

//proc�dure pour enlever un �l�ment du haut d'une pile
void pop(t_pile *, t_element *);

//focntion pour récupérer le nb d'éléments
int get_nb_elements(const t_pile * pile);

//fonction pour récupérer le sommet
int get_sommet(const t_pile * pile, t_element * elem);

//fonction pour récupérer la pile suivante
int get_suiv_sommet(const t_pile * pile, t_element * elem);
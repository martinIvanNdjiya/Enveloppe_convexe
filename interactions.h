/************************************************************************************
Par    : Martin Ivan Ndjiya et Judith Andrasko
Date   : Octobre 2026

Ce module implémente les déclarations des fonctions d'interaction avec l'utilisateur
et de gestion des entrées/sorties pour l'algorithme de l'enveloppe convexe.
On y retrouve les sous-programmes suivants :
- demander_mode   : Affiche le menu et valide le choix du mode d'exécution
					(aléatoire, fichier ou simulation).
- choisir_fichier: Demande, saisit et ouvre de manière sécurisée
				   un fichier texte en lecture.
- lire_points    : Lit le nombre de points, alloue dynamiquement 
				   le tableau et charge les coordonnées.
************************************************************************************/
// Évite d'inclure ce fichier d'en-tête plus d'une fois lors de la compilation
#pragma once

//Permet de désactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>    // Entrées/sorties standard 
#include<stdlib.h>   // Allocation dynamique et nombres aléatoires 
#include<math.h>     // Fonctions mathématiques 
#include<time.h>     // Fonctions liées au temps 

#include "tab_points.h"  // Type t_point utilisé dans le prototype de lire_points

/** DEMANDER_MODE
 * On affiche un menu qui propose les deux choix de modes d’exécution;
 * 1) mode aléatoire à 20 points,
 * 2) mode à partir d’un fichier-texte.
 * 3) mode simulation
 * Le choix de l’utilisateur doit être validé.
 * PARAMETRES: AUCUN (void)
 * RETOUR    : 1 (mode aleatoire) ou 2 (mode fichier-texte).
 */
int demander_mode(void);

/** CHOISIR_FICHIER
 * Permet de sélectionner un des fichiers .txt de points disponibles.
 * On demande et on saisit le nom d’un fichier .txt.
 * On tente ensuite d’ouvrir ce fichier en mode lecture.
 * PARAMETRES: Aucun (void)
 * RETOUR    : Le pointeur d'accès au fichier choisi (FILE *)
 */
FILE* choisir_fichier(void);

/** LIRE_POINTS
 * Lit tous les points du fichier et les retourne dans un tableau dynamique.
 */
t_point* lire_points(FILE* fichier, int* nb_pts);
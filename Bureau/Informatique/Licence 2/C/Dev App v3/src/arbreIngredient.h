/*
 * arbreIngredient.h
 *
 *  Created on: 17 déc. 2021
 *      Author: rayji
 */

#ifndef ARBREINGREDIENT_H_INCLUDED
#define ARBREINGREDIENT_H_INCLUDED

#include "ingredient.h"

typedef struct Noeud
{
    Ingredient i;
    struct Noeud *fg, *fd;
}NoeudI;

NoeudI* creerNoeud(Ingredient ing);

void afficherNoeud(NoeudI n);

void ajouterNoeud(NoeudI **n, Ingredient i);

void modifierNoeudPartie2(NoeudI **noeud, char *ancienNom, int nvId, char *nvNom, char *nvUnite);

void modifierNoeud(NoeudI **n, char* nomIngredient);

void afficherArbre(NoeudI *n, int compteur);

Ingredient rechercherIngredient(char *nomRecherche, NoeudI *n);

int compterNoeud(NoeudI *n);

NoeudI* suppMax(NoeudI **noeud);

void supprimerNoeud (NoeudI **noeud, char *nomRecherche);

void enregistrerArbre(NoeudI* noeud, FILE* fichier);

void libererArbre(NoeudI **n);

#endif // ARBREINGREDIENT_H_INCLUDED

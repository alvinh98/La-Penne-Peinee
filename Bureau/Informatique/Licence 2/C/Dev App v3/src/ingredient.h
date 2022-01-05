/*
 * ingredient.h
 *
 *  Created on: 17/12/2021
 *      Author: Hamaide Alvin
 */

#ifndef INGREDIENT_H_INCLUDED
#define INGREDIENT_H_INCLUDED

typedef struct
{
    int id;
    char *nom;
    char *unite;
}Ingredient;

Ingredient creerIngredient();
void afficherIngredient(Ingredient i);
void ajouterIngredientFichier(FILE *fichier, Ingredient i);
Ingredient lectureIngredientFichier(FILE *fichier);

#endif // INGREDIENT_H_INCLUDED



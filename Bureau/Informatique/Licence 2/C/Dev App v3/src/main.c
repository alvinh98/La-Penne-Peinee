/*
 ============================================================================
 Name        : main.c
 Author      : Hamaide Alvin
 Version     : 3.0
 Copyright   :
 Description : Contains every testing functions and the main function
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "ingredient.h"
#include "arbreIngredient.h"


void testIngredients()
{
    Ingredient i;
    FILE *fichier = fopen("ingredients.txt", "r+");

    i = creerIngredient();
    afficherIngredient(i);

    ajouterIngredientFichier(fichier, i);

    fseek(fichier,0,SEEK_SET);
    i = lectureIngredientFichier(fichier);
    afficherIngredient(i);
    fclose(fichier);
}

void testArbre()
{
	Ingredient ing;
	NoeudI *arbre;
	FILE *fichier = fopen("C:\\Users\\rayji\\Bureau\\ingredients.txt", "r+");

	//Putting the cursor at the beginning of the file just in case
	fseek(fichier,0,SEEK_SET);

	ing = lectureIngredientFichier(fichier);
	if (ing.id != -1)
    {
        arbre = creerNoeud(ing);
    }

	//While we don't receive a structure with the id -1, we keep reading ingredients
	while (ing.id != -1)
	{
		ing = lectureIngredientFichier(fichier);
		if (ing.id != -1)
		{
			ajouterNoeud(&arbre, ing);
		}
	}
	printf("-----------------------------\n");
	afficherArbre(arbre, -1);
	printf("=============================\n");

	afficherIngredient(rechercherIngredient("beurre", arbre));

	printf("%d\n", compterNoeud(arbre));

	printf("-----------------------------\n");
	modifierNoeud(&arbre, "oeufs");
	supprimerNoeud(&arbre, "lait");
	printf("=============================\n");

	afficherArbre(arbre, -1);

	libererArbre(&arbre);
	fclose(fichier);
}

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv)
{

	//testIngredients();
	//testArbre();
	NoeudI *arbre = NULL;
	FILE *fichier = fopen("ingredients.txt", "r+");
	Ingredient ing;
	int choixMenu = 0;

	while (ing.id != -1)
	{
		ing = lectureIngredientFichier(fichier);
		if (ing.id != -1)
		{
			ajouterNoeud(&arbre, ing);
		}
	}


	printf("----------MENU DES INGREDIENTS----------\n\n");

	while (choixMenu != 6)
	{
		printf("Que voulez-vous faire ?\n\n");
		printf("1- Visualiser tous les ingredients\n");
		printf("2- Rechercher un ingredient\n");
		printf("3- Ajouter un ingredient\n");
		printf("4- Modifier un ingredient\n");
		printf("5- Supprimer un ingredient\n");
		printf("6- Quitter\n\n");

		printf("Votre choix : ");
		scanf("%d", &choixMenu);
		printf("\n");

		switch(choixMenu)
		{
			case 1:
			{
				for (int i = 0; i < 50; i++)
				{
					printf("\n");
				}

				printf("-----------------------------\n");
				afficherArbre(arbre, -1);
			   	printf("=============================\n");
				printf("\n\n");
				break;
			}

			case 2:
			{
				for (int i = 0; i < 50; i++)
				{
					printf("\n");
				}

				char rechercheIngre[50];
				printf("Quel ingredient recherchez vous ? ");
				scanf("%s", rechercheIngre);

				printf("%s", rechercheIngre);

				ing = rechercherIngredient(rechercheIngre, arbre);

				printf("\n Nous avons trouve ceci : \n");
				afficherIngredient(ing);

				printf("\n\n");
				break;
			}

			case 3:
			{
				for (int i = 0; i < 50; i++)
				{
					printf("\n");
				}

				ing = creerIngredient();
				printf("\n");
				ajouterNoeud(&arbre, ing);

				printf("\n\n");
				break;
			}

			case 4:
			{
				for (int i = 0; i < 50; i++)
				{
					printf("\n");
				}

				char modifIngre[50];
				printf("Quel ingredient voulez vous modifier ? ");
				scanf("%s", modifIngre);

				modifierNoeud(&arbre, modifIngre);

				printf("\n\n");
				break;
			}

			case 5:
			{
				for (int i = 0; i < 50; i++)
				{
					printf("\n");
				}

				char supprIngre[50];
				printf("Quel ingredient voulez vous supprimer ? ");
				scanf("%s", supprIngre);

				supprimerNoeud(&arbre, supprIngre);

				printf("\n\n");
				break;
			}

			case 6:
			{
				fclose(fichier);
				FILE *reset = fopen("ingredients.txt","w");
				fclose(reset);

				FILE *fichier2 = fopen("ingredients.txt","r+");

				//enregistrerArbre(arbre, fichier2);

				fclose(fichier2);
				libererArbre(&arbre);
				break;
			}

			default:
			{
				for (int i = 0; i < 50; i++)
				{
					printf("\n");
				}

				printf("Choix invalide. ");

				printf("\n\n");
				break;
			}
		}
	}

	return 0;
}

/*
 * arbreIngredient.c
 *
 *  Created on: 17/12/2021
 *      Author: Hamaide Alvin
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "ingredient.h"
#include "arbreIngredient.h"
#include "comparaison.h"

/**
 *
 * @param i
 * @return
 */
NoeudI* creerNoeud(Ingredient ing)
{
    NoeudI *nouveau = (NoeudI*) malloc(sizeof(NoeudI));

    if (nouveau)
    {
        nouveau->i  = ing;
        nouveau->fg = NULL;
        nouveau->fd = NULL;
        return nouveau;
    }
    else
    {
        printf("Echec de creation\n");
    }
    return nouveau;
}


/**
 *
 * @param n
 */
void afficherNoeud(NoeudI n)
{
    afficherIngredient(n.i);
}


/**
 *
 * @param n
 * @param i
 */
void ajouterNoeud(NoeudI **n, Ingredient ing)
{
    if (*n == NULL)
    {
        *n = creerNoeud(ing);
    }
    //If the name of the ingredient appears later in the alphabetical order
    else if (comparaisonNom(ing.nom, ((*n)->i.nom)) == -1)
    {
        //Comparing to the right member
        ajouterNoeud(&(*n)->fd, ing);
    }
    //If the name of the ingredient appears earlier in the alphabetical order
    else if (comparaisonNom(ing.nom, ((*n)->i.nom)) == 1)
    {
        ajouterNoeud(&(*n)->fg, ing);
    }
    //If the names are the same
    else
    {
        //It means that the ingredient already is in the tree, we warn the user
        printf("L'ingredient est deja dans l'arbre\n");
    }
}


/**
 *
 * @param noeud
 * @param ancienNom
 * @param nvId
 * @param nvNom
 * @param nvUnite
 */
void modifierNoeudPartie2(NoeudI **noeud, char *ancienNom, int nvId, char *nvNom, char *nvUnite)
{
	//If ancienNom appears later in the alphabetical order
	    if (noeud != NULL && comparaisonNom(ancienNom, (*noeud)->i.nom) == -1)
	    {
	    	modifierNoeudPartie2(&(*noeud)->fd, ancienNom, nvId, nvNom, nvUnite);
	    }
	    //If ancienNom appears earlier in the alphabetical order
	    else if (*noeud != NULL && comparaisonNom(ancienNom, (*noeud)->i.nom) == 1)
	    {
	    	modifierNoeudPartie2(&(*noeud)->fg, ancienNom, nvId, nvNom, nvUnite);
	    }
	    //If we found the good ingredient
	    else if (noeud != NULL)
	    {
	    	//Modifying the ingredient with the new name, the new id and the new unity in the parameters
	    	(*noeud)->i.id = nvId;
	    	strcpy((*noeud)->i.nom, nvNom);
	    	strcpy((*noeud)->i.unite, nvUnite);
	    }
}


/**
 *
 * @param n
 * @param nomIngredient
 */
void modifierNoeud(NoeudI **noeud, char* nomIngredient)
{
	Ingredient ingreModif = rechercherIngredient(nomIngredient, *noeud);
	afficherIngredient(ingreModif);
	//Checking if the ingredient really exists
	if (comparaisonNom(ingreModif.nom, nomIngredient) == 0)
	{
		int choix = 0;
		printf("Que voulez-vous modifier ?\n\n");
		printf("1- Id de l'ingredient\n");
		printf("2- Nom de l'ingredient\n");
		printf("3- Unite de l'ingredient \n");
		printf("Votre choix (1, 2, ou 3) : ");

		scanf("%d", &choix);
		printf("\n");

		switch(choix)
		{
			case 1:
			{
				int nvId = 0;

				printf("Nouvel id de l'ingredient : ");
				scanf("%d", &nvId);

				//Going through the tree to find the good ingredient and modify it with those parameters
				modifierNoeudPartie2(noeud, ingreModif.nom, nvId, ingreModif.nom, ingreModif.unite);
				break;
			}

			case 2:
			{
				char *nvNom = "";

				printf("Nouveau nom de l'ingredient : ");
				scanf("%s", nvNom);

				//Going through the tree to find the good ingredient and modify it with those parameters
				modifierNoeudPartie2(noeud, ingreModif.nom, ingreModif.id, nvNom, ingreModif.unite);
				break;
			}

			case 3:
			{
				char *nvUnite = "";

				printf("Nouvelle unite de l'ingredient : ");
				scanf("%s",nvUnite);

				//Going through the tree to find the good ingredient and modify it with those parameters
				modifierNoeudPartie2(noeud, ingreModif.nom, ingreModif.id, ingreModif.nom, nvUnite);
				break;
			}

			default:
			{
				printf("Choix errone\n");
				break;
			}
		}
	}
	else
	{
		printf("Ingredient introuvable\n");
	}
}


/**
 *
 * @param n
 * @param compteur
 */
void afficherArbre(NoeudI *noeud, int compteur)
{
    //Counts the number of levels in the tree. Every time we call the function, it adds 1.
    compteur++;

    //If the structure isn't empty
    if (noeud != NULL)
    {
        //We first show the right member
        if (noeud->fd != NULL)
        {
            afficherArbre(noeud->fd, compteur);
        }

        //Then the current member
        for (int i = 0; i < compteur; i++)
        {
            printf("     ");
        }
        afficherNoeud(*noeud);

        //Finally, the left member
        if (noeud->fg != NULL)
        {
            afficherArbre(noeud->fg, compteur);
        }
    }
}


/**
 *
 * @param nomRecherche
 * @param n
 * @return
 */
Ingredient rechercherIngredient(char *nomRecherche, NoeudI *noeud)
{
    Ingredient ingre;
    ingre.id = -1;
    ingre.unite = (char*)malloc(5*sizeof(char));
	ingre.nom   = (char*)malloc(5*sizeof(char));
    strcpy(ingre.nom, "NULL");
    strcpy(ingre.unite , "NULL");

    //If nomRecherche appears later in the alphabetical order
    if (noeud != NULL && comparaisonNom(nomRecherche, noeud->i.nom) == -1)
    {
    	ingre = rechercherIngredient(nomRecherche, noeud->fd);
    }
    //If nomRecherche appears earlier in the alphabetical order
    else if (noeud != NULL && comparaisonNom(nomRecherche, noeud->i.nom) == 1)
    {
    	ingre = rechercherIngredient(nomRecherche, noeud->fg);
    }
    else if (noeud != NULL)
    {
    	ingre = noeud->i;
    }
    return ingre;
}


/**
 *
 * @param n
 * @return
 */
int compterNoeud(NoeudI *n)
{
	int compteur = 0;

	if(n != NULL)
    {
        //Counts the left, the right, and the current member
		compteur += compterNoeud(n->fg);
		compteur++;
		compteur += compterNoeud(n->fd);
	}
	return compteur;
}


/**
 *
 * @param noeud
 */
NoeudI* suppMax(NoeudI **noeud)
{
	 NoeudI *retour;
	if ((*noeud)->fd != NULL)
	{
		retour = *noeud;
		//Supressing the current member and replacing it by the left one
		(*noeud) = (*noeud)->fg;
	}
	else
	{
		retour = suppMax(&(*noeud)->fd);
	}
	return retour;
}


/**
 *
 * @param noeud
 * @param nomRecherche
 */
void supprimerNoeud (NoeudI **noeud, char *nomRecherche)
{
	//If nomRecherche appears later in the alphabetical order
	if (noeud != NULL && comparaisonNom(nomRecherche, (*noeud)->i.nom) == -1)
	{
	    supprimerNoeud(&(*noeud)->fd, nomRecherche);
	}
	//If ancienNom appears earlier in the alphabetical order
	else if (*noeud != NULL && comparaisonNom(nomRecherche, (*noeud)->i.nom) == 1)
	{
	    supprimerNoeud(&(*noeud)->fg, nomRecherche);
	}
	//If we found the good ingredient
	else if (noeud != NULL)
	{
		//If the right member is empty
	    if ((*noeud)->fd != NULL)
	    {
	    	//Supressing the current member and replacing it by the left one
	    	*noeud = (*noeud)->fg;
	    }
	    //If the left member is empty
	    else if ((*noeud)->fg != NULL)
	    {
	    	//Supressing the current member and replacing it by the right one
	    	*noeud = (*noeud)->fd;
	    }
	    else
	    {
	    	suppMax(&(*noeud)->fg);
	    }
	}
}


void enregistrerArbre(NoeudI* noeud, FILE* fichier)
{
	char c = ' ';
	fseek(fichier, 0, SEEK_SET);

	if (noeud->fd != NULL)
	{
		enregistrerArbre(noeud->fd, fichier);
	}

	if (noeud != NULL)
	{
		do
		{
			c = fgetc(fichier);

			//'n' is a random character chosen to enter the condition when the file is empty
			if (c < noeud->i.id || c != 'n')
			{
				while (c != '\n' && c != '\r' && !feof(fichier))
				{
					c = fgetc(fichier);
				}
			}
			else
			{
				while (c != '\n' && c != '\r' && !feof(fichier))
				{
					c = fgetc(fichier);
				}
				ajouterIngredientFichier(fichier, noeud->i);
			}
		}while (!feof(fichier) && c < noeud->i.id);

	}

	if (noeud->fg != NULL)
	{
		enregistrerArbre(noeud->fg, fichier);
	}
}


//Free every member of the tree on by one
/**
 *
 * @param n
 */
void libererArbre(NoeudI **n)
{
	if(*n != NULL)
    {
		libererArbre(&(*n)->fg);
		libererArbre(&(*n)->fd);
		free(*n);
	}
}

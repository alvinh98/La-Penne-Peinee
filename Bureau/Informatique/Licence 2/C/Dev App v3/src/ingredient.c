/*
 * ingredient.c
 *
 *  Created on: 17/12/2021
 *      Author: Hamaide Alvin
 */


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "ingredient.h"

/**
 *
 * @return
 */
Ingredient creerIngredient()
{
	Ingredient i;
	char tempNom[255];
	char tempUnite[255];

	//Putting the id directly in the structure and putting nom & unite in temporary variables
	printf("Saisissez l'id de l'ingredient : ");
	scanf("%d", &(i.id));

	printf("Saisissez le nom de l'ingredient : ");
	scanf("%s", tempNom);

	printf("Saisissez l'unite de l'ingredient : ");
	scanf("%s,", tempUnite);

	//Giving the necessary memory to i.nom based on tempNom content
	i.nom = (char*)malloc(strlen(tempNom)*sizeof(char));
	//Copying the content from tempNom in i.nom
	strcpy(i.nom, tempNom);

	//Giving the necessary memory to i.unite based on tempUnite content
	i.unite = (char*)malloc(strlen(tempUnite)*sizeof(char));
	////Copying the content from tempUnite in i.unite
	strcpy(i.unite, tempUnite);

	return i;
}


/**
 *
 * @param i
 */
void afficherIngredient(Ingredient i)
{
	printf("%d %s %s\n", i.id, i.nom, i.unite);
}


/**
 *
 * @param fichier
 * @param i
 */
void ajouterIngredientFichier(FILE *fichier, Ingredient i)
{
	//Putting the cursor at the end of the file
	fseek(fichier, 0, SEEK_END);

	//Writing i content in the file
	fprintf(fichier, "%d|%s|%s\n", i.id, i.nom, i.unite);
}


/**
 *
 * @param fichier
 * @return
 */
Ingredient lectureIngredientFichier(FILE *fichier)
{
	Ingredient ingre;

	char tempNom[255];
	char tempUnite[255];
	char c;

	//Counts the number of characters in tempNom and tempUnite
	int i = 0;

	//Checking if the cursor is at the end of the file or at an empty line
	c=fgetc(fichier);
	if (feof(fichier) || c=='\n' || c=='\r')
    {
		ingre.id = -1;
		return ingre;
	}
	//Coming back at the beginning of the line
	fseek(fichier, -1, SEEK_CUR);

	//Getting the id
	fscanf(fichier, "%d", &ingre.id);

	//Skipping the '|' character
	fseek(fichier, 1, SEEK_CUR);

	//Copying every character in tempNom until we meet the '|' character
	while(c != '|')
	{
		c = fgetc(fichier);
		tempNom[i] = c;
		i++;
	}

	//Last character is '|', so we replace it by this character
	tempNom[i-1] = '\0';

	//Giving the necessary memory to nom based on tempNom content
	ingre.nom = (char*)malloc(strlen(tempNom)*sizeof(char));
	//Copying the content from tempNom in nom
	strcpy(ingre.nom, tempNom);

	//Copying every character in tempNom until we meet the '\n' character
	i = 0;
	while(c != '\n')
	{
		c = fgetc(fichier);
		tempUnite[i] = c;
		i++;
	}
	//Last character is '\n', so we replace it by this character
	tempUnite[i-1] = '\0';

	//Giving the necessary memory to unite based on tempUnite content
	ingre.unite = (char*)malloc(strlen(tempUnite)*sizeof(char));
	//Copying the content from tempUnite in unite
	strcpy(ingre.unite, tempUnite);

	return ingre;
}

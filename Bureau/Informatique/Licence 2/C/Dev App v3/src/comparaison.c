/*
 * comparaison.c
 *
 *  Created on: 17/12/2021
 *      Author: Hamaide Alvin
 */


#include <string.h>
#include "comparaison.h"

int comparaisonNom(char *c1, char *c2)
{
    int tailleMin;
    if (strlen(c1) < strlen(c2))
    {
        tailleMin = strlen(c1);
    }
    else
    {
        tailleMin = strlen(c2);
    }

    for (int i = 0; i < tailleMin; i++)
    {
        if (c1[i] < c2[i])
        {
            return 1;
        }
        else if (c1[i] > c2[i])
        {
            return -1;
        }
    }
    return 0;
}

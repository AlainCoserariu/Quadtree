/**
 * @file affichage.h
 * @author COSERARIU Alain
 * @brief Module permettant d'afficher les objets du programmes
 * @date 2023-04-24
 * 
 * 
 */

#ifndef __AFFICHAGE__
#define __AFFICHAGE__

#include <MLV/MLV_all.h>

#include "particule.h"
#include "quadtree.h"
#include "utilitaire.h"

/**
 * @brief Initialise une fenêtre MLV
 * 
 */
void init_mlv();

/**
 * @brief Affiche tous les points sur une fenêtre MLV
 * 
 * @param tab Tableau de point à afficher
 * @param nb_points Nombre de points dans le tableau
 */
void affiche_points(Tab_point tab, unsigned int nb_points);

void affiche_quadtree(Quadtree quadtree);

#endif

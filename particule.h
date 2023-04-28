/**
 * @file particule.h
 * @author COSERARIU Alain
 * @brief Module permettant de gérer des structure de Quadtree
 * @date 2023-04-10
 * 
 * 
 */

#ifndef __PARTICULE__
#define __PARTICULE__

#include <stdlib.h>

#include "utilitaire.h"


typedef struct particule {
    struct particule* suivant; /* Pointeur vers un autre point d'un même noeud */
    Position* point; /* Pointeur vers un point */
} Particule;

typedef Particule* Interface; /* Tableau de particules chaînées */

typedef Position* Tab_point;

/**
 * @brief Indique si un point est présent dans un tableau de point
 * 
 * @param point 
 * @param tab Tableau de point
 * @param taille_tab 
 * @return int 1 : Le point est dans le tableau
 *             0 : Le point n'est pas dans le tableau
 */
int est_dans_tab_point(Position point, Tab_point tab, unsigned int taille_tab);

/**
 * @brief Remplit un tableau avec un certain nombre de points généré aléatoirement
 * 
 * @param tab
 * @param n Nombre de points à générer
 */
void remplit_tab_aleat(Tab_point tab, unsigned int n);

/**
 * @brief Ajoute une particule en fin de liste chaînée de particule
 * 
 * @param liste Liste de particule
 * @param particule Pointeur sur la particule à ajouter
 */
void ajoute_particule_liste(Particule** liste, Particule* particule);

#endif

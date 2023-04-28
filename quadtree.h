/**
 * @file quadtree.h
 * @author COSERARIU Alain
 * @brief Module permettant de gérer des structure de Quadtree
 * @date 2023-04-10
 * 
 * 
 */

#ifndef __QUADTREE__
#define __QUADTREE__

#include <stdlib.h>
#include <stdio.h>

#include "utilitaire.h"
#include "particule.h"

typedef struct cell_quadtree {
    int taille; /* Largeur de la zone couverte */
    int profondeur; /* Profondeur du noeud dans l'arbre */
    int nbp; /* Nombre de particules couverte par la zone */
    Position pos; /* Coordonnées du coins suprérieur gauche de la zone */
    Interface plist; /* Liste chaînées des particules du noeud */
    struct cell_quadtree* fils[4]; /* Tableau pointant sur ses 4 fils */
} Quadtree_Cell;

typedef Quadtree_Cell* Quadtree; /* Tableau de cellule de quadtree */

/**
 * @brief Initialise un tableau quadtree couvrant intégralement la zone 
 * jusqu'au pixel en fonction de la taille de la fenêtre
 * 
 * @param quadtree Quadtree à initialiser
 * @return int 1 : Tout c'est bien passé
 *          <= 0 : Une erreur s'est produite
 */
int initialise_quadtree(Quadtree* quadtree);

/**
 * @brief Ajoute un point dans un quadtree
 * 
 * @param quadtree Pointeur sur une cellule du quadtree
 * @param nb_point_max Nombre de points maximal d'une feuille
 * @param particule Pointeur sur une particule à ajouter
 */
void ajoute_point_quadtree(Quadtree_Cell* quadtree, int nb_point_max, Particule* particule);

#endif

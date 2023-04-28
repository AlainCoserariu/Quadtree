/**
 * @file utilitaire.h
 * @author COSERARIU Alain
 * @brief Module contenant des types global utilisable sur tout le projet
 * @date 2023-04-10
 * 
 * 
 */

#ifndef __UTILITAIRE__
#define __UTILITAIRE__

#include <stdlib.h>
#include <assert.h>

#define WIN_WIDTH 512
#define MIN_FEUILLE 1  /* Taille minimal d'une feuille */

typedef enum {
    ERREUR_ALLOCATION = -1,
    ERREUR_PARAMETRE = -2
} Erreur;

typedef struct {
    int x;
    int y;
} Position;

/**
 * @brief Calcule x à la puissance n
 * 
 * @param x
 * @param n 
 * @return int x puissance n
 */
int puissance(int x, int n);

/**
 * @brief Génére un nombre compris entre a et b (inclus)
 * 
 * @param a Borne inférieur
 * @param b Borne supérieur
 * @return int 
 */
int randint(unsigned int a, unsigned int b);

/**
 * @brief Indique si un point est dans un carré
 * 
 * @param position Position du coin supérieur gauche du carré
 * @param largeur Longueur du côté du carré
 * @param point Point à vérifier
 * @return int 
 */
int est_dans_carre(Position position, unsigned int largeur, Position point);

#endif

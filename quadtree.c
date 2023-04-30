#include "quadtree.h"

/**
 * @brief Calcule et renvoie le nombre de cellule d'un quadtree qui couvre la zone jusqu'au pixel
 * 
 * @return int Nombre de cellules
 */
static int compte_nb_cell() {
    int k;
    int exp_4 = 1;
    int nb_cell = 1;

    for (k = 1; k < WIN_WIDTH; k *= 2) {
        nb_cell += exp_4 * 4;
        exp_4 *= 4;
    }

    return nb_cell;
}

/**
 * @brief Initialise une cellule de Quadtree
 * 
 * @param cell 
 */
static void initialise_cell_quadtree(Quadtree_Cell* cell) {
    int k;
    for (k = 0; k < 4; ++k) {
        cell->fils[k] = NULL;
    }

    cell->pos.x = 0;
    cell->pos.y = 0;
    cell->plist = NULL;
    cell->nbp = 0;
    cell->taille = 0;
    cell->profondeur = 0;
}

/**
 * @brief Initialise toutes les cellules du quadtree
 * 
 * @param quadtree Tableau à initialiser
 */
static void initialise_toute_cellule(Quadtree quadtree) {    
    int k, l;

    for (k = 0; k < compte_nb_cell(); ++k) {
        initialise_cell_quadtree(&(quadtree[k]));
    }

    /* Traitement de la première cellule */
    quadtree[0].taille = WIN_WIDTH;
    quadtree[0].profondeur = 0;

    /* Traitement de toutes les cellules */
    for (k = 0; k < (compte_nb_cell() / 4); ++k) {

        /* Calcule de l'adresse de ses fils, leur position et leur taille */
        for (l = 0; l < 4; ++l) {
            quadtree[k].fils[l] = &(quadtree[4 * k + l + 1]);

            quadtree[k].fils[l]->profondeur = quadtree[k].profondeur + 1;
            quadtree[k].fils[l]->taille = quadtree[k].taille / 2;
        }
        /* Calcule la position de ses fils */
        quadtree[k].fils[0]->pos = quadtree[k].pos;
        
        quadtree[k].fils[1]->pos.x = quadtree[k].pos.x + quadtree[k].fils[1]->taille;
        quadtree[k].fils[1]->pos.y = quadtree[k].pos.y;

        quadtree[k].fils[2]->pos.x = quadtree[k].pos.x;
        quadtree[k].fils[2]->pos.y = quadtree[k].pos.y + quadtree[k].fils[2]->taille;

        quadtree[k].fils[3]->pos.x = quadtree[k].pos.x + quadtree[k].fils[3]->taille;
        quadtree[k].fils[3]->pos.y = quadtree[k].pos.y + quadtree[k].fils[3]->taille;
    }
}

int initialise_quadtree(Quadtree* quadtree) {
    int nb_cell = compte_nb_cell();

    *quadtree = malloc(sizeof(Quadtree_Cell) * nb_cell);
    if (*quadtree == NULL) {
        return ERREUR_ALLOCATION;
    }

    initialise_toute_cellule(*quadtree);
    return 1;
}

static void purge_cell_quadtree(Quadtree_Cell* quadtree, int nb_point_max) {
    Particule* liste = quadtree->plist;
    Particule* curseur = liste;
    Particule* tmp = curseur;
    quadtree->plist = NULL;

    /* Place les particules dans les fils du quadtree */
    while (curseur != NULL) {
        tmp = curseur->suivant;

        est_dans_carre(quadtree->fils[0]->pos, quadtree->fils[0]->taille, *(curseur->point));

        curseur->suivant = NULL;
        if (est_dans_carre(quadtree->fils[0]->pos, quadtree->fils[0]->taille, *(curseur->point))) {
            ajoute_point_quadtree(quadtree->fils[0], nb_point_max, curseur);
        } else if (est_dans_carre(quadtree->fils[1]->pos, quadtree->fils[1]->taille, *(curseur->point))) {
            ajoute_point_quadtree(quadtree->fils[1], nb_point_max, curseur);
        } else if (est_dans_carre(quadtree->fils[2]->pos, quadtree->fils[2]->taille, *(curseur->point))) {
            ajoute_point_quadtree(quadtree->fils[2], nb_point_max, curseur);
        } else if (est_dans_carre(quadtree->fils[3]->pos, quadtree->fils[3]->taille, *(curseur->point))) {
            ajoute_point_quadtree(quadtree->fils[3], nb_point_max, curseur);
        }

        curseur = tmp;
    }
}

void ajoute_point_quadtree(Quadtree_Cell* quadtree, int nb_point_max, Particule* particule) {
    quadtree->nbp++;
    
    ajoute_particule_liste(&(quadtree->plist), particule);

    if (quadtree->nbp > nb_point_max) {
        purge_cell_quadtree(quadtree, nb_point_max);
    }
}

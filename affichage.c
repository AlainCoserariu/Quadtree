#include "affichage.h"

void init_mlv() {
    MLV_create_window("Quadtree", "", WIN_WIDTH, WIN_WIDTH);
    MLV_clear_window(MLV_rgba(30, 30, 30, 255));
    MLV_actualise_window();
}

void affiche_points(Tab_point tab, unsigned int nb_points) {
    int k;

    for (k = 0; k < nb_points; ++k) {
        MLV_draw_pixel(tab[k].x, tab[k].y, MLV_COLOR_RED);
    }
}

void affiche_quadtree_cell(Quadtree_Cell quadtree, unsigned int nb_point_max) {
    if (quadtree.nbp == nb_point_max) {
        MLV_draw_filled_rectangle(quadtree.pos.x, quadtree.pos.y, quadtree.taille, quadtree.taille, MLV_rgba(220, 50, 50, 50));
        MLV_draw_rectangle(quadtree.pos.x, quadtree.pos.y, quadtree.taille, quadtree.taille, MLV_rgba(220, 50, 0, 200));    
    } else {
    MLV_draw_filled_rectangle(quadtree.pos.x, quadtree.pos.y, quadtree.taille, quadtree.taille, MLV_rgba(50, 220, 50, 50));
    MLV_draw_rectangle(quadtree.pos.x, quadtree.pos.y, quadtree.taille, quadtree.taille, MLV_rgba(0, 220, 0, 200));
    }
}

void affiche_quadtree(Quadtree quadtree, unsigned int nb_point_max) {
    if (quadtree->plist != NULL) {
        affiche_quadtree_cell(*quadtree, nb_point_max);
    }

    for (int k = 0; k < 4; ++k) {
        if (quadtree->fils[k] != NULL && quadtree->fils[k]->nbp > 0) {
            affiche_quadtree(quadtree->fils[k], nb_point_max);
        }
    }
}

/**
 * @file main.c
 * @author COSERARIU Alain
 * @brief Projet portant sur la gestion d'un grand nombre de points à l'aide 
 * d'une structure de donnée QuadTree
 * @date 2023-04-10
 * 
 */

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "affichage.h"
#include "quadtree.h"
#include "utilitaire.h"

void affiche_aide() {
    fprintf(stderr, "./quadtree [nombre de point] [distribution] [nombre de points maximal dans une feuille]\n\n");
    fprintf(stderr, "   -Nombre de points n          : 0 < n < %d\n", WIN_WIDTH * WIN_WIDTH);
    fprintf(stderr, "   -Distribution                : 0 = aléatoire 1 = clique souris\n");
    fprintf(stderr, "   -Nombre de points maximal  k : 1 < k < %d\n", WIN_WIDTH * WIN_WIDTH);
}

/**
 * @brief Initialise les strucutes de bases du projet
 * 
 * @param quadtree 
 * @param tab_point 
 * @param interface 
 * @param argv 
 * @return int 
 */
int init(Quadtree* quadtree, Tab_point* tab_point, Interface* interface, int nb_point) {
    int k;

    *tab_point = (Position*) malloc(nb_point * sizeof(Position));
    if (*tab_point == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation du tableau de point, fin du programme...\n");
        return ERREUR_ALLOCATION;
    }

    *interface = (Particule*) malloc(nb_point * sizeof(Particule));
    if (*interface == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de l'interface, fin du programme...\n");
        return ERREUR_ALLOCATION;
    }

    for (k = 0; k < nb_point; ++k) {
        (*interface)[k].point = &((*tab_point)[k]);
        (*interface)[k].suivant = NULL;
    }
    
    if (initialise_quadtree(quadtree) != 1) {
        fprintf(stderr, "Erreur lors de l'allocation du quadtree, fin du programme...\n");
        return ERREUR_ALLOCATION;
    }

    return 1;
}

int main_aleatoire(int nb_points, int nb_point_max) {
    Quadtree quadtree = NULL;
    Tab_point tab_point = NULL;
    Interface interface = NULL;

    int k;

    /* Initialisation */
    if (init(&quadtree, &tab_point, &interface, nb_points) != 1) {
        return ERREUR_ALLOCATION;
    }

    remplit_tab_aleat(tab_point, nb_points);

    init_mlv();

    /* Programme principale */

    for (k = 0; k < nb_points; ++k) {
        ajoute_point_quadtree(quadtree, nb_point_max, &(interface[k]));
    }

    /* Affichage */
    affiche_points(tab_point, nb_points);
    affiche_quadtree(quadtree, nb_point_max);
    MLV_actualise_window();
    
    MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);

    MLV_free_window();

    /* Libération de la mémoire */
    free(quadtree);
    free(tab_point);
    free(interface);

    return 1;
}

int main_souris(int nb_points, int nb_point_max) {
    Quadtree quadtree = NULL;
    Tab_point tab_point = NULL;
    Interface interface = NULL;

    MLV_Event event_type = MLV_NONE;
    Position souris;
    int nb_point_courent = 0;

    int k = 0;

    /* Initialisation */
    if (init(&quadtree, &tab_point, &interface, nb_points) != 1) {
        return ERREUR_ALLOCATION;
    }

    init_mlv();

    /* Programme principale */

    while (k < nb_points) {
        do {
            event_type = MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, &(souris.x), &(souris.y));
        } while (est_dans_tab_point(souris, tab_point, k) && event_type == MLV_MOUSE_BUTTON);
        
        if (event_type == MLV_MOUSE_BUTTON) {
            nb_point_courent++;

            while (est_dans_tab_point(souris, tab_point, k)) {
                event_type = MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, &(souris.x), &(souris.y));
            }

            tab_point[k] = souris;
            printf("%d %d\n", tab_point[k].x, tab_point[k].y);

            ajoute_point_quadtree(quadtree, nb_point_max, &(interface[k]));

            /* Affichage */
            MLV_clear_window(MLV_rgba(30, 30, 30, 255));
            affiche_points(tab_point, nb_point_courent);
            affiche_quadtree(quadtree, nb_point_max);
            MLV_actualise_window();

            k++;
        } else {
            free(quadtree);
            free(tab_point);
            free(interface);
            return 2;
        }

    }

    MLV_wait_keyboard(NULL, NULL, NULL);

    MLV_free_window();

    /* Libération de la mémoire */
    free(quadtree);
    free(tab_point);
    free(interface);

    return 1;
}

int main(int argc, char* argv[]) {
    int nb_points = 0;
    int distribution = 0; /* Indique le mode de distribution : 0 = aléatoire, 1 = clique souris */
    int nb_point_max = 1;  /* Nombre de points minimal dans une feuille */

    /* Gestion des paramètres */
    if (argc != 4) {
        fprintf(stderr, "Nombre de paramètre incohérent.\n\n");
        affiche_aide();
        return ERREUR_PARAMETRE;
    }

    nb_points = atoi(argv[1]);
    if (nb_points < 1 || nb_points > WIN_WIDTH * WIN_WIDTH) {
        fprintf(stderr, "Paramètre incorrecte\n\n");
        affiche_aide();
        return ERREUR_PARAMETRE;
    }

    distribution = atoi(argv[2]);
    if (distribution > 1 || distribution < 0) {
        fprintf(stderr, "Paramètre incorrecte\n\n");
        affiche_aide();
        return ERREUR_PARAMETRE;
    }

    nb_point_max = atoi(argv[3]);
    if (nb_point_max < 1 || nb_points > WIN_WIDTH * WIN_WIDTH) {
        fprintf(stderr, "Paramètre incorrecte\n\n");
        affiche_aide();
        return ERREUR_PARAMETRE;
    }

    /* Initialisation */
    srand(time(NULL));
    
    /* Programme principale */
    if (distribution == 0) {
        main_aleatoire(nb_points, nb_point_max);
    } else if (distribution == 1) {
        main_souris(nb_points, nb_point_max);
    }

    /* Libération de la mémoire */
    return 0;
}

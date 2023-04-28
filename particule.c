#include "particule.h"

int est_dans_tab_point(Position point, Tab_point tab, unsigned int taille_tab) {
    int k;

    for (k = 0; k < taille_tab; ++k) {
        if (point.x == tab[k].x && point.y == tab[k].y) {
            return 1;
        }
    }

    return 0;
}

void remplit_tab_aleat(Tab_point tab, unsigned int n) {
    int k;
    Position point;

    for (k = 0; k < n; ++k) {
        do {
            point.x = randint(0, WIN_WIDTH - 1);
            point.y = randint(0, WIN_WIDTH - 1);
        } while (est_dans_tab_point(point, tab, k));

        tab[k] = point;
    }
}

/* Fonction de gestion des listes de particules */

void ajoute_particule_liste(Particule** liste, Particule* particule) {
    Particule* curseur = *liste;
    
    if (*liste == NULL) {
        *liste = particule;
        return;
    }

    for (; curseur->suivant != NULL; curseur = curseur->suivant) {}

    curseur->suivant = particule;
}
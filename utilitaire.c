#include "utilitaire.h"

int randint(unsigned int a, unsigned int b) {
    assert(a <= b);
    return rand() % (b - a) + a;
}

int puissance(int x, int n) {
    for (int k = 1; k <= n; ++k) {
        x *= k;
    }

    return x;
}

int est_dans_carre(Position position, unsigned int largeur, Position point) {
    if (point.x >= position.x && point.x <= position.x + largeur - 1 && point.y >= position.y && point.y <= position.y + largeur - 1) {
        return 1;
    } else {
        return 0;
    }
}

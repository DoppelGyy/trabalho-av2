#include "cobra.h"

void cobra_inicializa(Cobra *c) {
    c->tamanho = 3;
    // Posição inicial no centro da grade 14x14
    c->corpo[0] = (Segmento){7, 7};
    c->corpo[1] = (Segmento){6, 7};
    c->corpo[2] = (Segmento){5, 7};
    c->dir_x = 1; // Começa andando para a direita
    c->dir_y = 0;
}

void cobra_move(Cobra *c, int cresce) {
    // Move os segmentos do corpo para a frente
    if (!cresce) {
        for (int i = c->tamanho - 1; i > 0; i--) {
            c->corpo[i] = c->corpo[i - 1];
        }
    } else {
        for (int i = c->tamanho; i > 0; i--) {
            c->corpo[i] = c->corpo[i - 1];
        }
        c->tamanho++;
    }
    // Atualiza a cabeça com base na direção atual
    c->corpo[0].x += c->dir_x;
    c->corpo[0].y += c->dir_y;
}

int cobra_colide_propria(Cobra *c) {
    for (int i = 1; i < c->tamanho; i++) {
        if (c->corpo[0].x == c->corpo[i].x && c->corpo[0].y == c->corpo[i].y) {
            return 1; // Colidiu
        }
    }
    return 0;
}
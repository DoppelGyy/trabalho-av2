#ifndef COBRA_H
#define COBRA_H

#define MAX_TAMANHO 200

typedef struct {
    int x;
    int y;
} Segmento;

typedef struct {
    Segmento corpo[MAX_TAMANHO];
    int tamanho;
    int dir_x; // Direção X (-1, 0, 1)
    int dir_y; // Direção Y (-1, 0, 1)
} Cobra;

void cobra_inicializa(Cobra *c);
void cobra_move(Cobra *c, int cresce);
int cobra_colide_propria(Cobra *c);

#endif
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "cobra.h"

#define GRADE 14
#define LARGURA_TELA 600
#define ALTURA_TELA 600

Cobra cobra;
Segmento comida;
int pontuacao = 0;
int game_over = 0;
int pausado = 0;
int intervalo_ms = 200; // Sua velocidade inicial personalizada

void gera_comida() {
    int valida;
    do {
        valida = 1;
        comida.x = rand() % GRADE;
        comida.y = rand() % GRADE;
        // Evita nascer em cima da cobra
        for (int i = 0; i < cobra.tamanho; i++) {
            if (cobra.corpo[i].x == comida.x && cobra.corpo[i].y == comida.y) {
                valida = 0;
                break;
            }
        }
    } while (!valida);
}

void reinicia_jogo() {
    cobra_inicializa(&cobra);
    pontuacao = 0;
    game_over = 0;
    intervalo_ms = 200;
    gera_comida();
}

void atualiza_titulo() {
    char titulo[100];
    sprintf(titulo, "Jogo da Cobrinha | Pontos: %d", pontuacao);
    glutSetWindowTitle(titulo);
}

void timer(int valor) {
    if (!game_over && !pausado) {
        int cresce = 0;
        
        // Calcula próxima posição da cabeça
        int proximo_x = cobra.corpo[0].x + cobra.dir_x;
        int proximo_y = cobra.corpo[0].y + cobra.dir_y;

        // Verifica colisão com paredes
        if (proximo_x < 0 || proximo_x >= GRADE || proximo_y < 0 || proximo_y >= GRADE) {
            game_over = 1;
        } else {
            // Verifica se comeu a comida
            if (proximo_x == comida.x && proximo_y == comida.y) {
                cresce = 1;
                pontuacao += 10; // 10 pontos por comida (sua regra)
                atualiza_titulo();
                gera_comida();
                
                // Mecânica de aceleração a cada 5 comidas
                if (pontuacao % 50 == 0 && intervalo_ms > 50) {
                    intervalo_ms -= 10;
                }
            }

            cobra_move(&cobra, cresce);

            // Verifica colisão consigo mesma
            if (cobra_colide_propria(&cobra)) {
                game_over = 1;
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(intervalo_ms, timer, 0);
}

void desenha_cenario() {
    float tamanho_casa = (float)LARGURA_TELA / GRADE;

    // Desenha a comida (Vermelha)
    glColor3f(0.9f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(comida.x * tamanho_casa + 2, comida.y * tamanho_casa + 2);
    glVertex2f((comida.x + 1) * tamanho_casa - 2, comida.y * tamanho_casa + 2);
    glVertex2f((comida.x + 1) * tamanho_casa - 2, (comida.y + 1) * tamanho_casa - 2);
    glVertex2f(comida.x * tamanho_casa + 2, (comida.y + 1) * tamanho_casa - 2);
    glEnd();

    // Desenha a cobra (Amarela - sua cor personalizada)
    glColor3f(0.95f, 0.85f, 0.1f);
    for (int i = 0; i < cobra.tamanho; i++) {
        glBegin(GL_QUADS);
        glVertex2f(cobra.corpo[i].x * tamanho_casa + 1, cobra.corpo[i].y * tamanho_casa + 1);
        glVertex2f((cobra.corpo[i].x + 1) * tamanho_casa - 1, cobra.corpo[i].y * tamanho_casa + 1);
        glVertex2f((cobra.corpo[i].x + 1) * tamanho_casa - 1, (cobra.corpo[i].y + 1) * tamanho_casa - 1);
        glVertex2f(cobra.corpo[i].x * tamanho_casa + 1, (cobra.corpo[i].y + 1) * tamanho_casa - 1);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    desenha_cenario();
    glutSwapBuffers();
}

void teclado(int tecla, int x, int y) {
    switch (tecla) {
        case GLUT_KEY_UP:
            if (cobra.dir_y == 0) { cobra.dir_x = 0; cobra.dir_y = 1; }
            break;
        case GLUT_KEY_DOWN:
            if (cobra.dir_y == 0) { cobra.dir_x = 0; cobra.dir_y = -1; }
            break;
        case GLUT_KEY_LEFT:
            if (cobra.dir_x == 0) { cobra.dir_x = -1; cobra.dir_y = 0; }
            break;
        case GLUT_KEY_RIGHT:
            if (cobra.dir_x == 0) { cobra.dir_x = 1; cobra.dir_y = 0; }
            break;
    }
}

void teclado_normal(unsigned char tecla, int x, int y) {
    if (tecla == 27) { // ESC
        exit(0);
    }
    if (tecla == 'p' || tecla == 'P') {
        pausado = !pausado;
    }
}

void mouse(int botao, int estado, int x, int y) {
    // Clique esquerdo reinicia se estiver em Game Over
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN && game_over) {
        reinicia_jogo();
    }
}

void inicializa_opengl() {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, LARGURA_TELA, 0, ALTURA_TELA);
}

int main(int argc, char **argv) {
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(LARGURA_TELA, ALTURA_TELA);
    glutCreateWindow("Jogo da Cobrinha | Pontos: 0");

    inicializa_opengl();
    reinicia_jogo();

    glutDisplayFunc(display);
    glutSpecialFunc(teclado);
    glutKeyboardFunc(teclado_normal);
    glutMouseFunc(mouse);
    glutTimerFunc(intervalo_ms, timer, 0);

    glutMainLoop();
    return 0;
}
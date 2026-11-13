# Jogo da Cobrinha (Snake) - AV2

Trabalho prático da disciplina Programação de Software Básico em C - Estácio Niterói.

Aluno: Angelo de Vargas Corrêa
Matrícula: `202603130991`
Professor: Wender Cris de Souza Firmino

Parâmetros de Personalização

Tamanho da Grade: $14 \times 14$
Velocidade Inicial: 200 ms
Cor da Cobra: Amarela
Pontos por Comida: 10

Compilação e Execução
No Windows (MinGW / MSYS2)
```bash
gcc main.c cobra.c -o jogo_cobrinha.exe -lfreeglut -lopengl32 -lglu32 -Wall
.\jogo_cobrinha.exe

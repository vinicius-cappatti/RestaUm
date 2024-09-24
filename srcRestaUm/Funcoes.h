/* ***********************************************************************
* PARTICIPANTES:
*    Thomaz de Souza Scopel (RA: 10417183)
*    Vinícius Sanches Cappatti (RA: 10418266)
*********************************************************************** */

#include <stdio.h>
#include <stdbool.h>

#ifndef Funcoes

/* ******************************************************************
* Struct Movimento representa um movimento com as caracteristicas:
* x0: linha de partida
* y0: coluna de partida
* xf: linha final
* yf: coluna final
* direcao: a direcao do movimento (cima, baixo, esquerda ou direita)
****************************************************************** */
typedef struct movimento{
    int x0;
    int y0;
    int xf;
    int yf;
    char direcao;
} Movimento;

/*Struct Historico eh uma fila de Movimentos*/
typedef struct historico{
    Movimento *listMovs;
    int tam;
    int inicio;
    int fim;
} Historico;

/*Funcoes do jogo Resta Um*/

int** criaTabuleiro();
bool posicaoValida(int **tabuleiro, int linhas, int colunas, int x, int y);
bool finalizou(int **tabuleiro, int **gabarito, int linhas, int colunas);
bool movimentoValido(int **tabuleiro, int x0, int y0, char direcao);
Movimento movimentaCima(int **tabuleiro, int x0, int y0);
Movimento movimentaDir(int **tabuleiro, int x0, int y0);
Movimento movimentaBaixo(int **tabuleiro, int x0, int y0);
Movimento movimentaEsq(int **tabuleiro, int x0, int y0);
bool haJogadasPosiveis(int **tabuleiro, int linhas, int colunas);
Historico jogaRestaUm(int **tabuleiro, int linhas, int colunas, int qtdPecas, int centroLin, int centroCol);

/*Funcoes da struct Historico*/

void init(Historico hist, int tam);
bool enfila(Historico hist, Movimento mov);
Movimento desenfila(Historico hist);
bool cheia(Historico hist);
bool vazia(Historico hist);

/*Funcoes da struct Movimento*/

void limpaMovimento(Movimento mov);
void printMov(Movimento mov);

#endif
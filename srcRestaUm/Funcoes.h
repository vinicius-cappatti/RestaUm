/* ***********************************************************************
* PARTICIPANTES:
*    Thomaz de Souza Scopel (RA: 10417183)
*    Vinícius Sanches Cappatti (RA: 10418266)
*********************************************************************** */

#include <stdio.h>
#include <stdbool.h>

#ifndef funcoes.h

bool posicaoValida(int **tabuleiro, int linhas, int colunas, int x, int y);
bool finalizou(int **tabuleiro, int **gabarito, int linhas, int colunas);
bool movimentoValido(int **tabuleiro, int x0, int y0, char direcao);
Movimento movimenta(int **tabuleiro, int x0, int y0, char direcao);
bool haJogadasPosiveis(int **tabuleiro, int linhas, int colunas);
Historico jogaRestaUm(int **tabuleiro, int linhas, int colunas, int qtdPecas, int centroLin, int centroCol);
void enfila(Historico hist, Movimento mov);
Movimento desenfila(Historico hist);
void limpaMovimento(Movimento mov);

typedef struct movimento{
    int x0;
    int y0;
    int xf;
    int yf;
} Movimento;

typedef struct historico{
    Movimento *listMovs;
    int tam;
} Historico;

#endif
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
bool movimenta(int **tabuleiro, int x0, int y0, char direcao);
bool haJogadasPosiveis(int **tabuleiro, int linhas, int colunas);
bool jogaRestaUm(int **tabuleiro, int linhas, int colunas, int qtdPecas, int centroLin, int centroCol);

#endif
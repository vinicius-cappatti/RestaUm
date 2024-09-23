/* ***********************************************************************
* PARTICIPANTES:
*    Thomaz de Souza Scopel (RA: 10417183)
*    Vinícius Sanches Cappatti (RA: 10418266)
*********************************************************************** */

#include <stdio.h>
#include <stdbool.h>

#ifndef funcoes.h

bool finalizou(int **tabuleiro, int **gabarito, int linhas, int colunas);
bool movimentoValido(int **tabuleiro, int x0, int y0, char direcao);
void movimenta(int **tabuleiro, int x0, int y0, char direcao);
bool jogaRestaUm(int **tabuleiro, int **gabarito, int linhas, int colunas, int contPecas);

#endif
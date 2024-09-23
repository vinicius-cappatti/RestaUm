/* ***********************************************************************
* PARTICIPANTES:
*    Thomaz de Souza Scopel (RA: 10417183)
*    Vinícius Sanches Cappatti (RA: 10418266)
*********************************************************************** */

#include "RestaUm.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool finalizou(int **tabuleiro, int **gabarito, int linhas, int colunas){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            if(tabuleiro[i][j] != gabarito[i][j]){ return false; }
        }
    }
    
    return true;
}

bool movimentoValido(int **tabuleiro, int x0, int y0, int xf, int yf){

    if(abs(xf - x0) > 2 || abs(yf - y0) > 2){ return false; } /*Tentativa de se mover mais que 2 casas em uma direção*/

    if(tabuleiro[x0][y0] == -1 || tabuleiro[xf][yf] == -1){ return false; } /*Posição inicial ou final fora do tabuleiro*/

    if(tabuleiro[x0][y0] == 0 || tabuleiro[xf][yf] == 1) { return false; } /*Posição inicial sem peça ou posiçã final ocupada*/

    if(xf > 6 || xf < 0 || yf > 6 || yf < 0){ return false; } /*Posição final fora do  array*/
    
    if(tabuleiro[x0 + 1][y0 + 1] != 1){ return false; } /*Todo movimento deve, obrigatoriamente, comer uma peça*/

    return true;
}
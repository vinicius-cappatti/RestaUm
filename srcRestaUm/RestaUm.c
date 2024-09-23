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

bool movimentoValido(int **tabuleiro, int x0, int y0, char direcao){

    /* ********************************************
    * Possiveis valores da variavel direcao sao:
    *   'c' quando mover para CIMA
    *   'b' quando mover para BAIXO
    *   'e' quando mover para a ESQUERDA
    *   'd' quando mover para a DIREITA
    ******************************************** */

    if(tabuleiro[x0][y0] < 1){ return false; }

    switch (direcao){
        case 'c':

            if(tabuleiro[x0 - 1][y0] != 1 || tabuleiro[x0 - 2][y0] != 0){ return false;}

            break;
        
        case 'b':

            if(tabuleiro[x0 + 1][y0] != 1 || tabuleiro[x0 + 2][y0] != 0){ return false;}

            break;

        case 'e':

            if(tabuleiro[x0][y0 - 1] != 1 || tabuleiro[x0][y0 - 2] != 0){ return false;}

            break;

        case 'd':

            if(tabuleiro[x0][y0 + 1] != 1 || tabuleiro[x0][y0 + 2] != 0){ return false;}

            break;
    }

    return true;
}

void movimenta(int **tabuleiro, int x0, int y0, char direcao){
    
    /* ********************************************
    * Possiveis valores da variavel direcao sao:
    *   'c' quando mover para CIMA
    *   'b' quando mover para BAIXO
    *   'e' quando mover para a ESQUERDA
    *   'd' quando mover para a DIREITA
    ******************************************** */

    tabuleiro[x0][y0] = 0; /*Remove a peça da posicao inicial*/

    if(direcao == 'c'){ /*Movimento para cima*/
        tabuleiro[x0 - 1][y0] = 0;
        tabuleiro[x0 - 2][y0] = 1;
    }

    if(direcao == 'b'){ /*Movimento para baixo*/
        tabuleiro[x0 + 1][y0] = 0;
        tabuleiro[x0 + 2][y0] = 1;
    }

    if(direcao == 'e'){ /*Movimento para esquerda*/
        tabuleiro[x0][y0 - 1] = 0;
        tabuleiro[x0][y0 - 2] = 1;
    }

    if(direcao == 'd'){ /*Movimento para direita*/
        tabuleiro[x0][y0 + 1] = 0;
        tabuleiro[x0][y0 + 2] = 1;
    }
}

bool jogaRestaUm(int **tabuleiro, int **gabarito, int linhas, int colunas){
    
    int xAtual = 0, yAtual = 0;

    if(finalizou(tabuleiro, gabarito, linhas, colunas)){
        return true;
    }

    for(int x0 = xAtual; x0 < linhas; x0++){
        
    }
}
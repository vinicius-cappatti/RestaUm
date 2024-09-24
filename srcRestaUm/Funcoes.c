/* ***********************************************************************
* PARTICIPANTES:
*    Thomaz de Souza Scopel (RA: 10417183)
*    Vinícius Sanches Cappatti (RA: 10418266)
*********************************************************************** */

#include "Funcoes.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
 
/*Metodo retorna se a casa tabuleiro[x][y] pode ser utilizada*/
bool posicaoValida(int **tabuleiro, int linhas, int colunas, int x, int y){
    if(x < 0 || x > linhas || y < 0 || y > linhas){ return false; } /*Verifica se as coordenadas estao dentro do vetor*/
    if(tabuleiro[x][y] == -1){ return false; } /*Casas com valor -1 sao invalidas para movimentacao de pecas*/

    return true;
}

/*Metodo que retorna se a matriz tabuleiro esta igual a matriz gabarito*/
bool finalizou(int **tabuleiro, int **gabarito, int linhas, int colunas){ 
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            if(tabuleiro[i][j] != gabarito[i][j]){ return false; }
        }
    }
    
    return true;
}

/*Metodo retorna se a peca da posicao tabuleiro[x0][y0] pode ser movida conforme a direcao*/
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

/*Metodo que realiza o movimento de tabuleiro[x0][y0] conforme parametro direcao e retorna o movimento*/
Movimento movimenta(int **tabuleiro, int x0, int y0, char direcao){

    /* ********************************************
    * Possiveis valores da variavel direcao sao:
    *   'c' quando mover para CIMA
    *   'b' quando mover para BAIXO
    *   'e' quando mover para a ESQUERDA
    *   'd' quando mover para a DIREITA
    ******************************************** */

    tabuleiro[x0][y0] = 0; /*Remove a peça da posicao inicial*/

    Movimento mov;

    if(direcao == 'c'){ /*Movimento para cima*/
        tabuleiro[x0 - 1][y0] = 0;
        tabuleiro[x0 - 2][y0] = 1;
        
        mov.x0 = x0;
        mov.y0 = y0;
        mov.xf = x0 - 2;
        mov.yf = y0;
    }

    if(direcao == 'b'){ /*Movimento para baixo*/
        tabuleiro[x0 + 1][y0] = 0;
        tabuleiro[x0 + 2][y0] = 1;
        
        mov.x0 = x0;
        mov.y0 = y0;
        mov.xf = x0 + 2;
        mov.yf = y0;
    }

    if(direcao == 'e'){ /*Movimento para esquerda*/
        tabuleiro[x0][y0 - 1] = 0;
        tabuleiro[x0][y0 - 2] = 1;
        
        mov.x0 = x0;
        mov.y0 = y0;
        mov.xf = x0;
        mov.yf = y0 - 2;
    }

    if(direcao == 'd'){ /*Movimento para direita*/
        tabuleiro[x0][y0 + 1] = 0;
        tabuleiro[x0][y0 + 2] = 1;
        
        mov.x0 = x0;
        mov.y0 = y0;
        mov.xf = x0;
        mov.yf = y0 + 2;
    }

    return mov;
}

/*Metodo retorna se ha pelo menos uma jogada possivel a ser feita*/
bool haJogadasPosiveis(int **tabuleiro, int linhas, int colunas){
    for(int x = 0; x < linhas; x++){
        for(int y = 0; y < colunas; y++){
            if(movimentoValido(tabuleiro, x, y, 'c')){ return true; } /*Verifica movimento para a cima*/
            if(movimentoValido(tabuleiro, x, y, 'd')){ return true; } /*Verifica movimento para a direita*/
            if(movimentoValido(tabuleiro, x, y, 'b')){ return true; } /*Verifica movimento para a baixo*/
            if(movimentoValido(tabuleiro, x, y, 'e')){ return true; } /*Verifica movimento para a esquerda*/
        }
    }

    return false;
}

/*Metodo com backtracking do resta um*/
Historico jogaRestaUm(int **tabuleiro, int linhas, int colunas, int qtdPecas, int centroLin, int centroCol){
    
    Historico hist;

    hist.listMovs = (Movimento*) malloc((qtdPecas - 1));

    for(int x = 0; x < linhas; x++){
        for(int y = 0; y < colunas; y++){
            if(posicaoValida(tabuleiro, linhas, colunas, x, y)){
                
                /*Testa com movimento para cima*/
                if(movimentoValido(tabuleiro, x, y, 'c')){
                    Movimento mov = movimenta(tabuleiro, x, y, 'c');
                    qtdPecas--;

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        /* **********************************************************************************
                        * TODO: implementar o que vai ser feito se encontrarmos um resultado de sucesso
                        * em que chegamos ao tabuleiro final esperado
                        ********************************************************************************** */
                    }

                }

                /*Testa com movimento para a direita*/
                if(movimentoValido(tabuleiro, x, y, 'd')){
                    movimenta(tabuleiro, x, y, 'd');
                    qtdPecas--;

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        /* **********************************************************************************
                        * TODO: implementar o que vai ser feito se encontrarmos um resultado de sucesso
                        * em que chegamos ao tabuleiro final esperado
                        ********************************************************************************** */
                    }

                }

                /*Testa com movimento para baixo*/
                if(movimentoValido(tabuleiro, x, y, 'b')){
                    movimenta(tabuleiro, x, y, 'b');
                    qtdPecas--;

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        /* **********************************************************************************
                        * TODO: implementar o que vai ser feito se encontrarmos um resultado de sucesso
                        * em que chegamos ao tabuleiro final esperado
                        ********************************************************************************** */
                    }

                }

                /*Testa com movimento para a esquerda*/
                if(movimentoValido(tabuleiro, x, y, 'e')){
                    movimenta(tabuleiro, x, y, 'e');
                    qtdPecas--;

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        /* **********************************************************************************
                        * TODO: implementar o que vai ser feito se encontrarmos um resultado de sucesso
                        * em que chegamos ao tabuleiro final esperado
                        ********************************************************************************** */
                    }

                }
            }
        }
    }
}

void enfila(Historico hist, Movimento mov){
    hist.listMovs[hist.tam] = mov;
}

Movimento desenfila(Historico hist){
    Movimento ret = hist.listMovs[hist.tam];
    limpaMovimento(hist.listMovs[hist.tam]);
    return ret;
}

void limpaMovimento(Movimento mov){
    mov.x0 = 0;
    mov.y0 = 0;
    mov.xf = 0;
    mov.yf = 0;
}
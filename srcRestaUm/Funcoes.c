/* ***********************************************************************
* PARTICIPANTES:
*    Thomaz de Souza Scopel (RA: 10417183)
*    Vinícius Sanches Cappatti (RA: 10418266)
*********************************************************************** */

#include "Funcoes.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
 
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

Movimento movimentaCima(int **tabuleiro, int x0, int y0){
    tabuleiro[x0][y0] = 0; /*Remove a peça da posicao inicial*/
    Movimento mov;
    
    tabuleiro[x0 - 1][y0] = 0;
    tabuleiro[x0 - 2][y0] = 1;
    
    mov.x0 = x0;
    mov.y0 = y0;
    mov.xf = x0 - 2;
    mov.yf = y0;
    mov.direcao = 'c'; /*Simboliza que a direcao do movimento eh para cima*/

    return mov;
}

Movimento movimentaDir(int **tabuleiro, int x0, int y0){
    tabuleiro[x0][y0] = 0; /*Remove a peça da posicao inicial*/
    Movimento mov;

    tabuleiro[x0][y0 + 1] = 0;
    tabuleiro[x0][y0 + 2] = 1;

    mov.x0 = x0;
    mov.y0 = y0;
    mov.xf = x0;
    mov.yf = y0 + 2;
    mov.direcao = 'd'; /*Simboliza que a direcao do tabuleiro eh para a direita*/

    return mov;
}

Movimento movimentaBaixo(int **tabuleiro, int x0, int y0){
    tabuleiro[x0][y0] = 0; /*Remove a peça da posicao inicial*/

    Movimento mov;

    tabuleiro[x0 + 1][y0] = 0;
    tabuleiro[x0 + 2][y0] = 1;

    mov.x0 = x0;
    mov.y0 = y0;
    mov.xf = x0 + 2;
    mov.yf = y0;
    mov.direcao = 'b'; /*Simboliza que a direcao do movimento eh para baixo*/

    return mov;
}

Movimento movimentaEsq(int **tabuleiro, int x0, int y0){
    tabuleiro[x0][y0] = 0; /*Remove a peça da posicao inicial*/

    Movimento mov;

    tabuleiro[x0][y0 - 1] = 0;
    tabuleiro[x0][y0 - 2] = 1;
    
    mov.x0 = x0;
    mov.y0 = y0;
    mov.xf = x0;
    mov.yf = y0 - 2;
    mov.direcao = 'e'; /*Simboliza que a direcao do movimento eh para a esquerda*/

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

    init(hist, qtdPecas - 1); /*Inicializa a fila do historico*/

    for(int x = 0; x < linhas; x++){
        for(int y = 0; y < colunas; y++){
            if(posicaoValida(tabuleiro, linhas, colunas, x, y)){
                
                /*Testa com movimento para cima*/
                if(movimentoValido(tabuleiro, x, y, 'c')){
                    Movimento mov = movimentaCima(tabuleiro, x, y);
                    enfila(hist, mov);
                    qtdPecas--;

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        return hist;
                    }

                    desenfila(hist);

                }

                /*Testa com movimento para a direita*/
                if(movimentoValido(tabuleiro, x, y, 'd')){
                    Movimento mov = movimentaDir(tabuleiro, x, y);
                    enfila(hist, mov);
                    qtdPecas--;

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        return hist;
                    }

                    desenfila(hist);
                }

                /*Testa com movimento para baixo*/
                if(movimentoValido(tabuleiro, x, y, 'b')){
                    Movimento mov = movimentaBaixo(tabuleiro, x, y);
                    enfila(hist, mov);
                    qtdPecas--;

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        return hist;
                    }

                    desenfila(hist);
                }

                /*Testa com movimento para a esquerda*/
                if(movimentoValido(tabuleiro, x, y, 'e')){
                    Movimento mov = movimentaEsq(tabuleiro, x, y);
                    enfila(hist, mov);
                    qtdPecas--;

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        return hist;
                    }

                    desenfila(hist);
                }
            }
        }
    }
}

void init(Historico hist, int tam){
    hist.inicio = -1;
    hist.fim = -1;
    hist.tam = tam;
    hist.listMovs = (Movimento*) malloc(hist.tam);
}

bool cheia(Historico hist){
    return hist.fim == hist.tam - 1;
}

bool vazia(Historico hist){
    return hist.inicio == -1;
}

bool enfila(Historico hist, Movimento mov){
    if(cheia(hist)){
        return false;
    }

    if(vazia(hist)){
        hist.inicio = 0;
    }

    hist.fim++;
    hist.listMovs[hist.fim] = mov;
    return true;
}

Movimento desenfila(Historico hist){
    if(vazia(hist)){
        return;
    }

    Movimento mov = hist.listMovs[hist.inicio];

    if(hist.inicio == hist.fim){
        hist.inicio = -1;
        hist.fim = -1;
    } else{
        hist.inicio++;
    }

    return mov;
}

void limpaMovimento(Movimento mov){
    mov.x0 = 0;
    mov.y0 = 0;
    mov.xf = 0;
    mov.yf = 0;
    mov.direcao = 0;
}

void printMov(Movimento mov){
    setlocale(LC_ALL, "pt_BR.UTF-8");

    switch (mov.direcao){
        case 'c':
            printf("Cima: ");
            break;

        case 'd':
            printf("Direita: ");
            break;
        case 'b':
            printf("Baixo: ");
            break;
        case 'e':
            printf("Esquerda: ");
            break;
        default:
            printf("Invalida!");
            return;
            break;
    }

    printf("(%d, %d) -> (%d, %d)", mov.x0, mov.y0, mov.xf, mov.yf);
}
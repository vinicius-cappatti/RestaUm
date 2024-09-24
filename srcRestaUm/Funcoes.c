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
#include <string.h>
 
 /*Funcao que le o arquivo de entrada e o converte em uma matriz*/
void lerTabuleiro(int **tabuleiro, int numLinhas, int numColunas, char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");  // Abre o arquivo em modo de leitura

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[numColunas + 3];  // Ajusta para possível '\n' e '\0'

    // Percorre o arquivo, lendo linha por linha
    for (int i = 0; i < numLinhas + 2; i++) {  // numLinhas + 2 devido à margem (#)
        if (fgets(linha, sizeof(linha), arquivo) == NULL) {
            printf("Erro ao ler o arquivo.\n");
            break;
        }

        // Remove a nova linha (\n) se estiver presente
        removeNovaLinha(linha);

        if (i == 0 || i == numLinhas + 1) {
            // Ignora a primeira e a última linha (margens de #)
            continue;
        }

        // Processa apenas as linhas internas (sem a margem)
        for (int j = 1; j <= numColunas; j++) {
            char aux = linha[j];
            
            while(aux != ' ' && aux != 'o' && aux != '#'){
                aux = linha[j + 1];    
            }
            
            if (aux == '#') {
                tabuleiro[i - 1][j - 1] = -1;
            } else if (aux == 'o') {
                tabuleiro[i - 1][j - 1] = 1;
            } else if (aux == ' ') {
                tabuleiro[i - 1][j - 1] = 0;
            }
            
        }
    }

    fclose(arquivo);  // Fecha o arquivo
}

void removeNovaLinha(char *linha) {
    size_t len = strlen(linha);
    if (len > 0 && linha[len - 1] == '\n') {
        linha[len - 1] = '\0';  // Remove o '\n'
    }
}

/*Metodo retorna se a casa tabuleiro[x][y] pode ser utilizada*/
bool posicaoValida(int **tabuleiro, int linhas, int colunas, int x, int y){
    if(x < 0 || x >= linhas || y < 0 || y >= colunas){ return false; } /*Verifica se as coordenadas estao dentro do vetor*/
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
bool movimentoValido(int **tabuleiro, int linhas, int colunas, int x0, int y0, char direcao){

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

            if((x0 - 1) < 0 || (x0 - 2) < 0){ return false; } /*Tentativa de se acessar memoria fora da matriz*/
            if(tabuleiro[x0 - 1][y0] != 1 || tabuleiro[x0 - 2][y0] != 0){ return false;}

            break;
        
        case 'b':

            if((x0 + 1) >= linhas || (x0 + 2) >= linhas){ return false; }
            if(tabuleiro[x0 + 1][y0] != 1 || tabuleiro[x0 + 2][y0] != 0){ return false;}

            break;

        case 'e':

            if((y0 - 1) < 0 || (y0 - 2) < 0){ return false; }
            if(tabuleiro[x0][y0 - 1] != 1 || tabuleiro[x0][y0 - 2] != 0){ return false;}

            break;

        case 'd':

            if((y0 + 1) >= colunas || (y0 + 2) >= colunas){ return false; }
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
            if(movimentoValido(tabuleiro, linhas, colunas, x, y, 'c')){ return true; } /*Verifica movimento para a cima*/
            if(movimentoValido(tabuleiro, linhas, colunas, x, y, 'd')){ return true; } /*Verifica movimento para a direita*/
            if(movimentoValido(tabuleiro, linhas, colunas, x, y, 'b')){ return true; } /*Verifica movimento para a baixo*/
            if(movimentoValido(tabuleiro, linhas, colunas, x, y, 'e')){ return true; } /*Verifica movimento para a esquerda*/
        }
    }

    return false;
}

/*Metodo com backtracking do resta um*/
Movimento** jogaRestaUm(int **tabuleiro, int linhas, int colunas, int qtdPecas, int centroLin, int centroCol, Movimento** historico, int *cont){
    
    for(int x = 0; x < linhas; x++){
        for(int y = 0; y < colunas; y++){
            if(posicaoValida(tabuleiro, linhas, colunas, x, y)){
                
                /*Testa com movimento para cima*/
                if(movimentoValido(tabuleiro, linhas, colunas, x, y, 'c')){
                    Movimento mov = movimentaCima(tabuleiro, x, y);
                    qtdPecas--;

                    historico[(*cont)] = &mov;
                    (*cont)++;
                    printMov(historico[(*cont)]);
                    printMov(&mov);

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol, historico, cont);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        return historico;
                    }

                    printf("Deletando: ");
                    printMov(historico[(*cont)]);
                    printf("\n");
                    limpaMovimento(historico[(*cont)]);
                    (*cont)--;
                }

                /*Testa com movimento para a direita*/
                if(movimentoValido(tabuleiro, linhas, colunas, x, y, 'd')){
                    Movimento mov = movimentaDir(tabuleiro, x, y);
                    qtdPecas--;

                    historico[(*cont)] = &mov;
                    (*cont)++;
                    printMov(historico[(*cont)]);
                    printMov(&mov);

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol, historico, cont);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        return historico;
                    }
                    
                    printf("Deletando: ");
                    printMov(historico[(*cont)]);
                    printf("\n");
                    limpaMovimento(historico[(*cont)]);
                    (*cont)--;
                }

                /*Testa com movimento para baixo*/
                if(movimentoValido(tabuleiro, linhas, colunas, x, y, 'b')){
                    Movimento mov = movimentaBaixo(tabuleiro, x, y);
                    qtdPecas--;

                    historico[(*cont)] = &mov;
                    (*cont)++;
                    printMov(historico[(*cont)]);
                    printMov(&mov);

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol, historico, cont);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        return historico;
                    }

                    printf("Deletando: ");
                    printMov(historico[(*cont)]);
                    printf("\n");
                    limpaMovimento(historico[(*cont)]);
                    (*cont)--;
                }

                /*Testa com movimento para a esquerda*/
                if(movimentoValido(tabuleiro, linhas, colunas, x, y, 'e')){
                    Movimento mov = movimentaEsq(tabuleiro, x, y);
                    qtdPecas--;

                    historico[(*cont)] = &mov;
                    (*cont)++;
                    printMov(historico[(*cont)]);
                    printMov(&mov);

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol, historico, cont);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        return historico;
                    }
                    

                    printf("Deletando: ");
                    printMov(historico[(*cont)]);
                    printf("\n");
                    limpaMovimento(historico[(*cont)]);
                    (*cont)--;
                }
            }
        }
    }
}

void limpaMovimento(Movimento *mov){
    mov->x0 = 0;
    mov->y0 = 0;
    mov->xf = 0;
    mov->yf = 0;
    mov->direcao = 0;
}

void printMov(Movimento *mov){
    printf("(%d, %d) -> (%d, %d)\n", mov->x0, mov->y0, mov->xf, mov->yf);
}
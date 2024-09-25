/* ***********************************************************************
* PARTICIPANTES:
*    Thomaz de Souza Scopel (RA: 10417183)
*    Vinícius Sanches Cappatti (RA: 10418266)
*********************************************************************** */
 
/*Funcao que le o arquivo de entrada e o converte em uma matriz*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Funcoes.h"

void removeNovaLinha(char *linha) {
    char *pos;
    if ((pos = strchr(linha, '\n')) != NULL) {
        *pos = '\0';
    }
}

int** copiaTabuleiro(int **tabuleiro, int linhas, int colunas){
    int** tabuleiro2 = (int**) malloc(linhas * sizeof(int*));

    for(int i = 0; i < linhas; i++){
        tabuleiro2[i] = tabuleiro[i];
    }
}

/* Função que lê o arquivo de entrada e o converte em uma matriz */
void lerTabuleiro(int **tabuleiro, int numLinhas, int numColunas, char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");  // Abre o arquivo em modo de leitura
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[200000];  // Ajusta para possível '\n' e '\0'

    // Percorre o arquivo, lendo linha por linha
    for (int i = 0; i < numLinhas + 2; i++) {  // numLinhas + 2 devido à margem (#)
        fgets(linha, sizeof(linha), arquivo);  // Lê uma linha do arquivo
        removeNovaLinha(linha);  // Remove a nova linha (\n) se estiver presente

        if (i == 0 || i == numLinhas + 1) {
            // Ignora a primeira e a última linha (margens de #)
            continue;
        }

        // Processa apenas as linhas internas (sem a margem)
        for (int j = 1; j <= numColunas; j++) {  // Começa em 1 e vai até numColunas
            char caractere = linha[j];  // Pega o caractere correspondente

            // Converte os caracteres para os valores da matriz
            if (caractere == '#') {
                tabuleiro[i - 1][j - 1] = -1;  // Margem
            } else if (caractere == 'o') {
                tabuleiro[i - 1][j - 1] = 1;   // Espaço ocupado
            } else if (caractere == ' ') {
                tabuleiro[i - 1][j - 1] = 0;   // Espaço vazio
            }
        }
    }

    fclose(arquivo);  // Fecha o arquivo
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
bool movimentoValido(int **tabuleiro, int tamanho, int x0, int y0, int xf, int yf){
	
	if(tabuleiro[x0][y0] != 1){ return false; }
	
	if(xf < 0 || xf >= tamanho || yf < 0 || yf >= tamanho){ return false; } // Fora dos limites da matriz
	
	if(tabuleiro[xf][yf] != 0){ return false; }
	
	int xmedia = (x0 + xf) / 2;
	int ymedia = (y0 + yf) / 2;
	
	if(tabuleiro[xmedia][ymedia] != 1){ return false; }

	return true;
}

Movimento movimenta(int **tabuleiro, int x0, int y0, int xf, int yf){
    tabuleiro[x0][y0] = 0;
    tabuleiro[xf][yf] = 1;

    int xmedia = (x0 + xf) / 2;
    int ymedia = (y0 + yf) / 2;

    tabuleiro[xmedia][ymedia] = 0;

    Movimento mov;

    mov.x0 = x0;
    mov.xf = xf;
    mov.y0 = y0;
    mov.yf = yf;

    return mov;
}

/*Metodo retorna se ha pelo menos uma jogada possivel a ser feita*/
bool haJogadasPosiveis(int **tabuleiro, int linhas, int colunas){
    for(int x = 0; x < linhas; x++){
        for(int y = 0; y < colunas; y++){
            if(movimentoValido(tabuleiro, linhas, x, y, x - 2, y)){ return true; } /*Verifica movimento para a cima*/
            if(movimentoValido(tabuleiro, linhas, x, y, x, y + 2)){ return true; } /*Verifica movimento para a direita*/
            if(movimentoValido(tabuleiro, linhas, x, y, x + 2, y)){ return true; } /*Verifica movimento para a baixo*/
            if(movimentoValido(tabuleiro, linhas, x, y, x, y - 2)){ return true; } /*Verifica movimento para a esquerda*/
        }
    }

    return false;
}

/*Metodo com backtracking do resta um*/
Movimento** jogaRestaUm(int **tabuleiro, int linhas, int colunas, int qtdPecas, int centroLin, int centroCol, Movimento** historico, int cont){
    
    for(int x = 0; x < linhas; x++){
        for(int y = 0; y < colunas; y++){
            if(posicaoValida(tabuleiro, linhas, colunas, x, y)){
                
                /*Testa com movimento para cima*/
                if(movimentoValido(tabuleiro, linhas, x, y, x - 2, y)){
                    Movimento mov = movimenta(tabuleiro, x, y, x - 2, y);
                    qtdPecas--;

                    historico[cont] = &mov;
                    cont++;

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol, historico, cont);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        return historico;
                    }

                    limpaMovimento(historico[cont]);
                    cont--;
                }

                /*Testa com movimento para a direita*/
                if(movimentoValido(tabuleiro, linhas, x, y, x, y + 2)){
                    Movimento mov = movimenta(tabuleiro, x, y, x, y + 2);
                    qtdPecas--;

                    historico[cont] = &mov;
                    cont++;

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol, historico, cont);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        return historico;
                    }
                    
                    limpaMovimento(historico[cont]);
                    cont--;
                }

                /*Testa com movimento para baixo*/
                if(movimentoValido(tabuleiro, linhas, x, y, x + 2, y)){
                    Movimento mov = movimenta(tabuleiro, x, y, x + 2, y);
                    qtdPecas--;

                    historico[cont] = &mov;
                    cont++;
                    printMov(&mov);

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol, historico, cont);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        return historico;
                    }

                    limpaMovimento(historico[cont]);
                    cont--;
                }

                /*Testa com movimento para a esquerda*/
                if(movimentoValido(tabuleiro, linhas, x, y, x, y - 2)){
                    Movimento mov = movimenta(tabuleiro, x, y, x, y - 2);
                    qtdPecas--;

                    historico[cont] = &mov;
                    cont++;
                    printMov(&mov);

                    if(qtdPecas > 1 && haJogadasPosiveis(tabuleiro, linhas, colunas)){
                        jogaRestaUm(tabuleiro, linhas, colunas, qtdPecas, centroLin, centroCol, historico, cont);
                    } else if(qtdPecas == 1 && tabuleiro[centroLin][centroCol] == 1){
                        return historico;
                    }
                    
                    limpaMovimento(historico[cont]);
                    cont--;
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
}

void printMov(Movimento *mov){
    setlocale(LC_ALL, "pt_BR.UTF-8");
    printf("(%d, %d) -> (%d, %d)\n", mov->x0, mov->y0, mov->xf, mov->yf);
}
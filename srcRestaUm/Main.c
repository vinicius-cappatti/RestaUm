/* ***********************************************************************
 * PARTICIPANTES:
 *    Thomaz de Souza Scopel (RA: 10417183)
 *    Vinícius Sanches Cappatti (RA: 10418266)
 *********************************************************************** */


/*Bibliotecas utilizadas*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

/*Arquivo com as funcoes implementadas para o jogo de resta um*/
#include "Funcoes.h"

/*Constantes do programa*/

#define TAMANHO 7
#define LIN_CENTRO 3
#define COL_CENTRO 3
#define NUM_INI_PECAS 32

int main(){
    setlocale(LC_ALL, "pt_BR.UTF-8");

    /* ******************************************
     * Matriz que contem um tabuleiro de Resta um
     * onde:
     * -1 representa uma posicao onde nao ha casa
     * 0 representa uma casa vazia
     * 1 representa uma casa ocupada
     ****************************************** */

    int **tabuleiro = (int **)malloc(TAMANHO * sizeof(int *));
    if (tabuleiro == NULL){
        fprintf(stderr, "Erro ao alocar memória para o tabuleiro.\n");
        return 1; // Ou outra forma de lidar com o erro
    }

    /*Alocacao da memoria para as linhas da matriz*/
    for (int i = 0; i < TAMANHO; i++){
        tabuleiro[i] = (int *)malloc(TAMANHO * sizeof(int));
        if (tabuleiro[i] == NULL){
            fprintf(stderr, "Erro ao alocar memória para a linha %d do tabuleiro.\n", i);
            // Libere a memória já alocada antes de retornar
            for (int k = 0; k < i; k++){
                free(tabuleiro[k]);
            }
            free(tabuleiro);
            return 1; // Ou outra forma de lidar com o erro
        }
        // Inicializa a linha
        for (int j = 0; j < TAMANHO; j++){
            tabuleiro[i][j] = 0;
        }
    }

    // Chama a função para ler o tabuleiro do arquivo e armazená-lo na matriz
    lerTabuleiro(tabuleiro, TAMANHO, TAMANHO, "entrada.txt");

    int **tabuleiro2 = copiaTabuleiro(tabuleiro, TAMANHO, TAMANHO);

    Movimento** jogadas = (Movimento**) malloc((NUM_INI_PECAS - 1) * sizeof(Movimento*));
    for (int i = 0; i < (NUM_INI_PECAS - 1); i++) {
        jogadas[i] = (Movimento*) malloc(sizeof(Movimento));
    }
    
    int cont = 0;
    /*Chamada do backtracking*/
    
    printf("*** JOGO DE RESTA UM ***\nA execução pode demorar alguns minutos.");

    jogadas = jogaRestaUm(tabuleiro, TAMANHO, TAMANHO, NUM_INI_PECAS, LIN_CENTRO, COL_CENTRO, jogadas, cont);

    printf("Resultado encontrado!\n");

    if(jogadas == NULL){
        printf("Erro na criação das jogadas.");
        return 1;
    }

    int tam = sizeof(jogadas) / sizeof(Movimento*);
    /*TODO: Implementar a saida em arquivo*/

    for(int i = 0; i < tam; i++){
        printMov(jogadas[i]);
    }

    /*Imprimir as jogadas no arquivo de saida*/
    
    FILE *saida;

    saida = fopen("restaum.out", "w");

    if(saida == NULL){
        printf("Erro ao abrir o arquivo de saída.");
        return 1;
    }

    for(int i = 0; i < sizeof(jogadas); i++){

        fprintf(saida, "#########\n");
        for(int x = 0; x < TAMANHO; x++){
            fprintf(saida, "#");
            for(int y = 0; y < TAMANHO; y++){
                if(tabuleiro2[x][y] == -1){
                    fprintf(saida, "#");
                } else if(tabuleiro2[x][y] == 0){
                    fprintf(saida, " ");
                } else if(tabuleiro2[x][y] == 1){
                    fprintf(saida, "o");
                }
            }
            fprintf(saida, "#\n");
        }
        fprintf(saida, "#########\n");

        movimenta(tabuleiro2, jogadas[i]->x0, jogadas[i]->y0, jogadas[i]->xf, jogadas[i]->yf);
    }
    
    fclose(saida);

    printf("Resultado salvo em restaum.out\n");
    // Libera a memória alocada dinamicamente antes de finalizar o programa
    free(jogadas);

    for (int i = 0; i < TAMANHO; i++){
        free(tabuleiro[i]);
    }
    free(tabuleiro);

    for (int i = 0; i < TAMANHO; i++){
        free(tabuleiro2[i]);
    }
    free(tabuleiro2);

    return 0;
}
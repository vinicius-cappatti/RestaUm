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

    // Exibe a matriz do tabuleiro para conferir o resultado
    for (int i = 0; i < TAMANHO; i++){
        for (int j = 0; j < TAMANHO; j++){
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    Movimento** jogadas = (Movimento**) malloc((NUM_INI_PECAS - 1) * sizeof(Movimento*));
    int cont = 0;
    /*Chamada do backtracking*/
    
    jogadas = jogaRestaUm(tabuleiro, TAMANHO, TAMANHO, NUM_INI_PECAS, LIN_CENTRO, COL_CENTRO, jogadas, cont);

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
    

    // Libera a memória alocada dinamicamente antes de finalizar o programa
    for (int i = 0; i < TAMANHO; i++){
        free(tabuleiro[i]);
    }
    free(tabuleiro);

    return 0;
}
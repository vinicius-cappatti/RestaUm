/* ***********************************************************************
 * PARTICIPANTES:
 *  Thomaz de Souza Scopel (RA: 10417183)
 *  Vinícius Sanches Cappatti (RA: 10418266)
 * OBJETIVO:
 *  Criar um programa utilizando Backtracking que solucione um jogo 
 *  de Resta Um de forma que, ao final, a peca restante esteja sempre
 *  na posicao central do tabuleiro
 ************************************************************************/


/*Bibliotecas utilizadas*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

/*Arquivo com as funcoes implementadas para o jogo de resta um*/
#include "Funcoes.h"

int **tabuleiro;
int **tabuleiro2;
Movimento **jogadas;

int main(int argc, char **argv){
    setlocale(LC_ALL, "pt_BR.UTF-8");

    tabuleiro = inicializaTabuleiro(); // Alocacao da memoria dinamica do tabuleiro
    if(tabuleiro == NULL){
        return 1;
    }

    // Chama a função para ler o tabuleiro do arquivo e armazená-lo na matriz
    if (argc > 1) {
        lerTabuleiro(argv[1]);
    }
    else {
        lerTabuleiro("entrada.txt");
    }

    tabuleiro2 = copiaTabuleiro(tabuleiro, TAMANHO); // tabuleiro2 sera utilizado posteriormente para imprimir a saida

    jogadas = (Movimento**) malloc(NUM_INI_PECAS * sizeof(Movimento*)); // Lista contendo os movimentos feitos para resolver o jogo

    /*Chamada do backtracking*/
    
    printf("*** JOGO DE RESTA UM ***\nA execução pode demorar um pouco.\n");

    jogaRestaUm(NUM_INI_PECAS); 
    
    if(jogadas == NULL){
        printf("Erro na criação das jogadas.\n");
        return 1;
    }

    printf("Resultado encontrado!\nPassos para se resolver o resta um:\n");

    printJogadas();

    /*Imprimir as jogadas no arquivo de saida*/
    
    imprimeSaida("restaum.out");

    printf("Resultado salvo em restaum.out\n");

    // Libera a memória alocada dinamicamente antes de finalizar o programa
    for(int i = 0; i < cont; i++){ free(jogadas[i]); }
    free(jogadas);

    for (int i = 0; i < TAMANHO; i++){ free(tabuleiro[i]); }
    free(tabuleiro);

    for (int i = 0; i < TAMANHO; i++){ free(tabuleiro2[i]); }
    free(tabuleiro2);

    return 0;
}
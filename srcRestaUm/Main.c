/* ***********************************************************************
* PARTICIPANTES:
*    Thomaz de Souza Scopel (RA: 10417183)
*    Vinícius Sanches Cappatti (RA: 10418266)
*********************************************************************** */

/*Arquivo com as funcoes implementadas para o jogo de resta um*/
#include "Funcoes.h"

/*Bibliotecas utilizadas*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

/*Constantes do programa*/
#define MAX_LINHAS 7
#define MAX_COLUNAS 7
#define LIN_CENTRO 3
#define COL_CENTRO 3
#define NUM_INI_PECAS 32

int main(){
    setlocale(LC_ALL, "pt_BR.UTF-8"); 

    /*Determinacao da posicao inicial do tabuleiro*/
    int **tabuleiro = criaTabuleiro();

    /* ****************************************
    * TODO: implementar a leitura do 
    * arquivo entrada.txt
    * CONSIDERAR:
    * 1. Margem de # em torno do tabuleiro
    * 2. Casas invalidas = '#'
    * 3. Casas vazias = ' ' (espaco)
    * 4. Casas cheias = 'o'
    **************************************** */
    
    /*Variaveis auxiliares para o backtracking*/

    Movimento** auxListMovs = (Movimento**) malloc((NUM_INI_PECAS - 1) * sizeof(Movimento*));
    int cont = 0;
    int *pcont = &cont;
    
    /*Chamada do backtracking*/
    
    Movimento** jogadas = jogaRestaUm(tabuleiro, MAX_LINHAS, MAX_COLUNAS, NUM_INI_PECAS, LIN_CENTRO, COL_CENTRO, auxListMovs, pcont);

    if(jogadas == NULL){
        printf("Erro na criação das jogadas.");
        return 1;
    }

    int tam = sizeof(jogadas) / sizeof(Movimento*);
    /*TODO: Implementar a saida em arquivo*/

    for(int i = 0; i < tam; i++){
        printMov(*jogadas[i]);
    }

    return 0;
}
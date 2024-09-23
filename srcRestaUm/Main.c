/* ***********************************************************************
* PARTICIPANTES:
*    Thomaz de Souza Scopel (RA: 10417183)
*    Vinícius Sanches Cappatti (RA: 10418266)
*********************************************************************** */

/*Funcoes implementadas para o jogo de resta um*/
#include "RestaUm.h"

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

    int linVazIni, colVazIni;
    int tabuleiro[MAX_LINHAS][MAX_COLUNAS] = {       
        {-1, -1,  1,  1,  1, -1, -1},
        {-1, -1,  1,  1,  1, -1, -1},
        { 1,  1,  1,  1,  1,  1,  1},
        { 1,  1,  1,  0,  1,  1,  1},
        { 1,  1,  1,  1,  1,  1,  1},
        {-1, -1,  1,  1,  1, -1, -1},
        {-1, -1,  1,  1,  1, -1, -1},
    };

    printf("*** RESTA UM ***\n");
    printf("Defina a linha onde estará a posição vazia inical");
    scanf("%d", &linVazIni);
    printf("Defina a coluna onde estará a posição vazia inical");
    scanf("%d", &colVazIni);

    while(!posicaoValida(tabuleiro, MAX_LINHAS, MAX_COLUNAS, linVazIni, colVazIni)){
        printf("POSIÇÃO INVÁLIDA");
        printf("Defina a linha onde estará a posição vazia inical");
        scanf("%d", &linVazIni);
        printf("Defina a coluna onde estará a posição vazia inical");
        scanf("%d", &colVazIni);
    }

    if(linVazIni != 3 && colVazIni != 3){
        tabuleiro[3][3] = 1;
        tabuleiro[linVazIni][colVazIni] = 0;
    }
    
    return 0;
}
/* ***********************************************************************
* PARTICIPANTES:
*    Thomaz de Souza Scopel (RA: 10417183)
*    Vinícius Sanches Cappatti (RA: 10418266)
*********************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#ifndef FUNCOES_H
#define FUNCOES_H

/*Constantes do programa*/

#define TAMANHO 7
#define CENTRO 3
#define NUM_INI_PECAS 32

/* ******************************************************************
* Struct Movimento representa um movimento com as caracteristicas:
* x0: linha de partida
* y0: coluna de partida
* xf: linha final
* yf: coluna final
* direcao: a direcao do movimento (cima, baixo, esquerda ou direita)
****************************************************************** */
typedef struct movimento{
    int x0;
    int y0;
    int xf;
    int yf;
} Movimento;

/*Variaveis globais*/

/* ******************************************
* Matriz que contem um tabuleiro de Resta um
* onde:
* -1 representa uma posicao onde nao ha casa
* 0 representa uma casa vazia
* 1 representa uma casa ocupada
****************************************** */
extern int **tabuleiro;

//Copia da matriz tabuleiro que eh usada na saida do programa
extern int **tabuleiro2;

//Historico de jogadas
extern Movimento** jogadas;

//Contador utilizado no backtracking
static int cont = 0;

/*Funcoes do jogo Resta Um*/

int** inicializaTabuleiro();
void lerTabuleiro(char *nomeArquivo);
int** copiaTabuleiro();
void removeNovaLinha(char *linha);
bool movimentoValido(int x0, int y0, int xf, int yf);
void movimenta(int x0, int y0, int xf, int yf);
void desfazMovimento(int x0, int y0, int xf, int yf);
bool iteraBacktracking(int qtdPecas, int x0, int y0, char direcao);
int defineXf(int x, char direcao);
int defineYf(int y, char direcao);
bool jogaRestaUm(int qtdPecas);
void limpaMovimento(Movimento *mov);
void printMov(Movimento *mov);
void imprimeSaida(char *nomeArquivo);
void printHistorico();

#endif
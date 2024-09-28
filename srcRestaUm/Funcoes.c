/* ***********************************************************************
* PARTICIPANTES:
*    Thomaz de Souza Scopel (RA: 10417183)
*    Vinícius Sanches Cappatti (RA: 10418266)
*********************************************************************** */
 
/*Funcao que le o arquivo de entrada e o converte em uma matriz*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Funcoes.h"

void removeNovaLinha(char *linha) {
    char *pos;
    if ((pos = strchr(linha, '\n')) != NULL) {
        *pos = '\0';
    }
}

int** inicializaTabuleiro(){
    bool sucesso = true;

    int **tabuleiro = (int **) malloc (TAMANHO * sizeof(int *));
    if (tabuleiro == NULL){
        fprintf(stderr, "Erro ao alocar memória para o tabuleiro.\n");
        sucesso = false; // Ou outra forma de lidar com o erro
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
            sucesso = false;
        }
        
        // Inicializa a linha
        for (int j = 0; j < TAMANHO; j++){
            tabuleiro[i][j] = 0;
        }
    }

    return tabuleiro;
}

int** copiaTabuleiro(){
    int** tabuleiro2 = (int**) malloc(TAMANHO * sizeof(int*));

    for(int x = 0; x < TAMANHO; x++){
        tabuleiro2[x] = (int*) malloc(TAMANHO * sizeof(int));
    }

    for(int i = 0; i < TAMANHO; i++){
        for(int j = 0; j < TAMANHO; j++){
            tabuleiro2[i][j] = tabuleiro[i][j];
        }
    }

    return tabuleiro2;
}

/* Função que lê o arquivo de entrada e o converte em uma matriz */
void lerTabuleiro(char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");  // Abre o arquivo em modo de leitura
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[200000];  // Ajusta para possível '\n' e '\0'

    // Percorre o arquivo, lendo linha por linha
    for (int i = 0; i < TAMANHO + 2; i++) {  // TAMANHO + 2 devido à margem (#)
        fgets(linha, sizeof(linha), arquivo);  // Lê uma linha do arquivo
        removeNovaLinha(linha);  // Remove a nova linha (\n) se estiver presente

        if (i == 0 || i == TAMANHO + 1) {
            // Ignora a primeira e a última linha (margens de #)
            continue;
        }

        // Processa apenas as linhas internas (sem a margem)
        for (int j = 1; j <= TAMANHO; j++) {  // Começa em 1 e vai até numColunas
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
bool posicaoValida(int x, int y){
    if(x < 0 || x >= TAMANHO || y < 0 || y >= TAMANHO){ return false; } /*Verifica se as coordenadas estao dentro do vetor*/
    if(tabuleiro[x][y] == -1){ return false; } /*Casas com valor -1 sao invalidas para movimentacao de pecas*/

    return true;
}

/*Metodo retorna se a peca da posicao tabuleiro[x0][y0] pode ser movida conforme a direcao*/
bool movimentoValido(int x0, int y0, int xf, int yf){
	
	if(tabuleiro[x0][y0] != 1){ return false; }
	
	if(xf < 0 || xf >= TAMANHO || yf < 0 || yf >= TAMANHO){ return false; } // Fora dos limites da matriz
	
	if(tabuleiro[xf][yf] != 0){ return false; }
	
	int xmedia = (x0 + xf) / 2;
	int ymedia = (y0 + yf) / 2;
	
	if(tabuleiro[xmedia][ymedia] != 1){ return false; }

	return true;
}

void movimenta(int x0, int y0, int xf, int yf){
    tabuleiro[x0][y0] = 0; /*Posicao inicial do movimento*/
    tabuleiro[xf][yf] = 1; /*Posicao final do movimento*/

    int xmedia = (x0 + xf) / 2;
    int ymedia = (y0 + yf) / 2;

    /*Representa a casa onde esta a peca que sai do tabuleiro*/
    tabuleiro[xmedia][ymedia] = 0; 

    Movimento mov;

    mov.x0 = x0;
    mov.xf = xf;
    mov.y0 = y0;
    mov.yf = yf;

    jogadas[cont] = (Movimento*) malloc(sizeof(Movimento));
    *jogadas[cont] = mov;
    cont++;
}

void desfazMovimento(int x0, int y0, int xf, int yf){
    tabuleiro[x0][y0] = 1; /*Retorna a peca para a posicao inicial*/
    tabuleiro[xf][yf] = 0; /*Esvazia a casa da posicao final*/
    
    int xmedia = (x0 + xf) / 2;
    int ymedia = (y0 + yf) / 2;

    /*Insere de volta no tabuleiro a peca que havia sido retirada*/
    tabuleiro[xmedia][ymedia] = 1;
}

/*Metodo retorna se ha pelo menos uma jogada possivel a ser feita*/
bool haJogadasPosiveis(){
    for(int x = 0; x < TAMANHO; x++){
        for(int y = 0; y < TAMANHO; y++){
            if(movimentoValido(x, y, x - 2, y)){ return true; } /*Verifica movimento para a cima*/
            if(movimentoValido(x, y, x, y + 2)){ return true; } /*Verifica movimento para a direita*/
            if(movimentoValido(x, y, x + 2, y)){ return true; } /*Verifica movimento para a baixo*/
            if(movimentoValido(x, y, x, y - 2)){ return true; } /*Verifica movimento para a esquerda*/
        }
    }

    return false;
}

/* Variaveis globais (tabuleiro, TAMANHO da matriz, historico) 
*  Fluxograma: avaliar entrada/saida, transformar a entrada no padrao do programa como matriz,
*              avaliar movimentos validos (se a peça pode ser movida), fazer busca pra cada um 
*              dos movientos validos, ir gravando no historico como stack os movimentos
* 
*
*/

void iteraBacktracking(int qtdPecas, int c, int x0, int y0, char direcao){

    if(qtdPecas == 1 && tabuleiro[CENTRO][CENTRO] == 1){
        return;
    }

    int meio = TAMANHO / 2;

    int xf = defineXf(x0, direcao);
    int yf = defineYf(y0, direcao);

    if(movimentoValido(x0, y0, xf, yf)){

        movimenta(x0, y0, xf, yf);

        if(qtdPecas > 1 && haJogadasPosiveis()){
            jogaRestaUm(qtdPecas - 1, c + 1);
        }
        
        //printf("Limpando movimento para a esquerda");
        limpaMovimento(jogadas[cont - 1]); /*Retira o movimento do historico*/
        cont--;
        desfazMovimento(x0, y0, xf, yf); /*Retorna o tabuleiro para a posicao anterior ao movimento*/
    }    
}

int defineXf(int x, char direcao){
    switch (direcao){
        case 'c':
            return x - 2;
        case 'b':
            return x + 2;
        case 'd':
        case 'e':
            return x;
        default:
            return -1;
    }
}

int defineYf(int y, char direcao){
    switch (direcao){
        case 'c':
        case 'b':
            return y;
        case 'd':
            return y + 2;
        case 'e':
            return y - 2;
        default:
            return -1;
    }
}

/*Metodo com backtracking do resta um*/
void jogaRestaUm(int qtdPecas, int c){
    if(qtdPecas == 1 && tabuleiro[CENTRO][CENTRO] == 1){
        return;
    }

    for(int x = 0; x < TAMANHO; x++){
        for(int y = 0; y < TAMANHO; y++){
            if(posicaoValida(x, y) && qtdPecas > 1){
                /*Testa com movimento para cima*/
                iteraBacktracking(qtdPecas, c, x, y, 'c');
                /*Testa com movimento para baixo*/
                iteraBacktracking(qtdPecas, c, x, y, 'b');
                /*Testa com movimento para esquerda*/
                iteraBacktracking(qtdPecas, c, x, y, 'e');
                /*Testa com movimento para cima*/
                iteraBacktracking(qtdPecas, c, x, y, 'd');
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
    printf("(%d, %d) -> (%d, %d)\n", mov->x0, mov->y0, mov->xf, mov->yf);
}

void imprimeSaida(char *nomeArquivo){
    FILE *saida;

    saida = fopen(nomeArquivo, "w");

    if(saida == NULL){
        printf("Erro ao abrir o arquivo de saída.");
        return;
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

        movimenta(jogadas[i]->x0, jogadas[i]->y0, jogadas[i]->xf, jogadas[i]->yf);
    }
    
    fclose(saida);
}

void printHistorico(){
    for(int i = 0; i < cont; i++){
        printMov(jogadas[i]);
    }
}
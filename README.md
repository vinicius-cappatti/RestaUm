# RestaUm

## Participantes
|Nome|RA|
|---|---|
|Thomaz de Souza Scopel| 10417183|
|Vinícius Sanches Cappatti| 10418266|

## Objetivo
objetivo deste trabalho é implementar uma técnica de backtrack para resolver o problema de um jogo de tabuleiro conhecido como Resta um. No início do jogo, temos 33 buracos e 32 pinos dispostos em forma de cruz, com a posição central vazia.

![Tabuleiro de Resta Um](imagensREADME/image.png)

Ao executar um movimento válido na horizontal ou na vertical, os pinos serão gradual- mente removidos do tabuleiro. Um movimento válido é descrito da seguinte maneira. Sejam três posições (A, B, C) consecutivas no tabuleiro (na horizontal ou na vertical), com A e B pre- enchidas e C vazia. O movimento válido consiste em eliminar a peça que está na posição B e mover a peça que está em A para a posição vazia C.

![Exemplo de movimento válido](imagensREADME/image-1.png)

O objetivo do jogo é, após 31 movimentos válidos, obter apenas o pino central na posição central do tabuleiro (aquela que estava vazia no início). Seu programa deve, no final, imprimir uma sequência de movimentos que leva à configuração final desejada e também salvar em arquivo.

![Posiçao final esperada](imagensREADME/image-2.png)

## Instruções de Uso para Compilação

**Compilar:** 
```bash
gcc -o restaUm.exe srcRestaUm\Main.c srcRestaUm\Funcoes.c 
```

**Execução:**

A execução pode ser feita de duas maneiras:
- passando o caminho do arquivo de execução por terminal
```bash
.\restaUm.exe .\srcRestaUm\entrada.txt
```
 - ou executar se o arquivo de entrada estiver na mesma pasta
 ```bash
.\restaUm.exe
```

## Link para explicação

## Referências bibliográficas
1. CUNHA, Jair Ferreira da. Resta Um - Busca de Estratégias na Resolução [doi:10.11606/D.55.2021.tde-29032021-095422]. São Carlos : Instituto de Ciências Matemáticas e de Computação, University of São Paulo, 2021. Master's Dissertation in Mestrado Profissional em Matemática em Rede Nacional.
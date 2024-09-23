## Condições de parada para o backtracking
**1. Somente há um pino:**
     **1.Se o pino está na posição [4][4] do tabuleiro:** Solução viável encontrada.
     **2. Se o pino não está na posição [4][4] do tabuleiro:** Não é uma solução viável.
**2. Há 2 ou mais pinos:**
     1.Dado que um pino está em [i][j], se as posições adjascentes (conjunto {[i-1][j], [i+1][j], [i][j-1] e [i][j+1]}) estão vazias ou não podem ser utilizadas, então não é possível uma solução viável.  
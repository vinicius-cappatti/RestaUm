CC = gcc
CFLAGS = -g -IincludeRestaUm  # Gera símbolos de depuração e inclui cabeçalhos
SRC = srcRestaUm/Main.c srcRestaUm/Funcoes.c
OBJ = main.o funcoes.o
TARGET = output/restaUm.exe 

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir output  
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o
	rm -f output/restaUm.exe  # Remove o executável da pasta output


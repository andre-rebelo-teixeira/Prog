CFLAGS=-Wall -std=c11 -O3

output: main.o tabuleiro.o Conversor.o Ajuda.o Restricoes.o UserInput.o pecas.o modo_p1.o modo_p2.o disparo.o modo_j1.o 
	gcc $(CFLAGS) main.o tabuleiro.o Conversor.o Ajuda.o Restricoes.o UserInput.o pecas.o modo_p1.o modo_p2.o disparo.o modo_j1.o -o wargame -lm
 
tabuleiro.o: tabuleiro.c
	gcc $(CFLAGS) -c tabuleiro.c

Conversor.o: Conversor.c
	gcc $(CFLAGS) -c Conversor.c

Ajuda.o: Ajuda.c
	gcc $(CFLAGS) -c Ajuda.c
	
Restricoes.o: Restricoes.c
	gcc $(CFLAGS) -c Restricoes.c

UserInput.o: UserInput.c
	gcc $(CFLAGS) -c UserInput.c

pecas.o: pecas.c
	gcc $(CFLAGS) -c pecas.c

modo_p1.o: modo_p1.c
	gcc $(CFLAGS) -c modo_p1.c

modo_p2.o: modo_p2.c
	gcc $(CFLAGS) -c modo_p2.c

disparo.o: disparo.c
	gcc $(CFLAGS) -c disparo.c

modo_j1.o: modo_j1.c
	gcc $(CFLAGS) -c modo_j1.c

clean:
	rm *.o wargame
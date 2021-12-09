#compilation flags asked for this specific project
CFLAGS=-Wall -std=c11 -g

output: main.o sort.o reader.o add.o auxiliar.o selector.o restrictions.o readFiles.o userInput.o print.o
	gcc $(CFLAGS) main.o sort.o reader.o add.o auxiliar.o selector.o restrictions.o readFiles.o userInput.o print.o -o covid19
	
main.o: main.c
	gcc $(CFLAGS) -c main.c

sort.o: sort.c
	gcc $(CFLAGS) -c sort.c

reader.o: reader.c
	gcc $(CFLAGS) -c reader.c 

add.o: add.c 
	gcc $(CFLAGS) -c add.c

auxiliar.o: auxiliar.c
	gcc $(CFLAGS) -c auxiliar.c

selector.o: selector.c
	gcc $(CFLAGS) -c selector.c

restrictions.o: restrictions.c
	gcc $(CFLAGS) -c restrictions.c

readFiles.o : readFiles.c
	gcc $(CFLAGS) -c readFiles.c

userInput.o: userInput.c
	gcc $(CFLAGS) -c userInput.c

print.o : print.c
	gcc $(CFLAGS) -c print.c

clean:
	rm *.o covid19 
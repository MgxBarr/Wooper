img: main.o fonctions.o 
	gcc main.o fonctions.o -o img -Wall
fonctions.o: fonctions.c fonctions.h
	gcc -c fonctions.c  -o fonctions.o -Wall
main.o: main.c fonctions.h
	gcc -c main.c -o main.o -Wall
clean:
	rm -f *.o

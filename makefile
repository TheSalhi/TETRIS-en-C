all: TETRIS

TETRISS.o: TETRISS.c
	gcc -c TETRISS.c -o TETRISS.o
TETRIS: TETRISS.o 
	gcc TETRISS.o -o TETRIS 

	
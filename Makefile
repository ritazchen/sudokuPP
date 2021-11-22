cc = gcc
cflags = -lpthread
ompflags = -fopenmp

all:
	$(cc) -o sud sudoku.c
	$(cc) -o sudT sudokuPthreads.c $(cflags)
	$(cc) -o sudOMP sudokuOMP.c $(ompflags)

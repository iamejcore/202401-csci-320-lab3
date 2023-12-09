#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "lab3.h"

extern int** sudoku_board;
int* validation;

int** read_board_from_file(char* filename){
    FILE *fp = NULL;
    sudoku_board = (int**)malloc(sizeof(int*)*ROW_SIZE);
    for(int row = 0; row < ROW_SIZE; row++)
	    sudoku_board[row] = (int*)malloc(sizeof(int)*COL_SIZE);
    

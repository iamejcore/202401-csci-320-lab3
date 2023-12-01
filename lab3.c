#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "lab3.h"

extern int **sudoku_board;
extern int *worker_validation;

typedef struct {
    int id;
    int starting_row;
    int ending_row;
    int starting_col;
    int ending_col;
} param_struct;


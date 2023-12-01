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

int **read_board_from_file(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open file %s\n", filename);
        return NULL;
    }

    int **board = (int **)malloc(9 * sizeof(int *));
    for (int row = 0; row < 9; row++) {
        board[row] = (int *)malloc(9 * sizeof(int));
        for (int col = 0; col < 9; col++) {
            if (fscanf(fp, "%d", &board[row][col]) != 1) {
                fclose(fp);
                return NULL;
            }
        }
    }
fclose(fp);
    return board;
}

int exists(int element, int *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == element) {
            return 1;
        }
    }
    return 0;
}

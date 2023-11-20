#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "lab3.h"

extern int** sudoku_board;
int* worker_validation;

int** read_board_from_file(char* filename){
    FILE *fp = NULL;
    int** board = NULL;
if (fp != NULL) {
        board = (int**)malloc(9 * sizeof(int*));
        for (int row = 0; row < 9; row++) {
            board[row] = (int*)malloc(9 * sizeof(int));
            for (int col = 0; col < 9; col++) {
                if (fscanf(fp, "%d", &board[row][col]) != 1) {
                    fclose(fp);
                    return NULL;
                }
            }
        }
        fclose(fp);
    }

    return board;
}


int is_board_valid(){
    pthread_t* tid;  /* the thread identifiers */
    pthread_attr_t attr;
    param_struct* parameter;
    
   pthread_attr_init(&attr);
    
}

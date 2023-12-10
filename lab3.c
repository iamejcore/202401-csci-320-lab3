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
    
fp = fopen(filename,"r");
    for(int i = 0; i < ROW_SIZE; i++)
        for(int j = 0; j < COL_SIZE; j++) 
            fscanf(fp, "%d%*c", &sudoku_board[i][j]);


    for(int i = 0; i<ROW_SIZE; i++){
        for(int j = 0; j<COL_SIZE; j++) printf("%d ", sudoku_board[i][j]);
        printf("\n");
    }

    fclose(fp);
    return sudoku_board;
}

void* validate(void* param){
    param_struct* p = (param_struct*) param;
    int id = param->id;
    int startrow = param->starting_row; //start row//
    int endrow = param->ending_row; //end row//
    int startcol = param->starting_col; //start column//
    int endcol = param->ending_col; //end column//
    int arr[9] = {0,0,0,0,0,0,0,0,0};
    int current;
    validation[id] = 1;

for(int r = startrow; r <= endrow; r++){
        for(int c = startcol; c <= endcol; c++){
            current = sudoku_board[r][c];
            arr[current - 1] = 1;
        }
    }
    
    for(int i = 0; i < 9; i++)
        if(arr[i] != 1) validation[id] = 0;
    
    
}

int is_board_valid(){

    pthread_t* tid;  /* the thread identifiers */
    pthread_attr_t attr;
    tid = (pthread_t*) malloc(sizeof(int*) * NUM_OF_THREADS);
    param_struct* parameter = (param_struct*) malloc(sizeof(param_struct) * NUM_OF_THREADS);
    validation = (int*) malloc(sizeof(int) * 27);
    int num = 0;

for(int i = 0; i < ROW_SIZE; i++){
        parameter[num].id = num;
        parameter[num].starting_row = i;
        parameter[num].starting_col = 0;
        parameter[num].ending_row = i;
        parameter[num].ending_col = COL_SIZE - 1;

	pthread_create(&tid[num], NULL, validate, &parameter[num]);
        num++;
    }


 for(int i = 0; i < COL_SIZE; i++){
        parameter[num].id = num;
        parameter[num].starting_row = 0;
        parameter[num].starting_col = i;
        parameter[num].ending_row = COL_SIZE - 1;
        parameter[num].ending_col = i;

        pthread_create(&tid[num], NULL, validate, &parameter[num]);
        num++;
    }


 int r = 0, c = 0;
    for(int i = 0; i < NUM_OF_SUBGRIDS; i++){
        parameter[num].id = num;
        parameter[num].starting_row = r;
        parameter[num].starting_col = c;
        parameter[num].ending_row = r + 2;
        parameter[num].ending_col = c + 2;

        pthread_create(&tid[num], NULL, validate, &parameter[num]);
        num++;
	if(c == 6){
            r += 3;
            c = 0;
        } 
        else c += 3;
    }

    
    for(int i = 0; i< NUM_OF_THREADS; i++) 
        pthread_join(tid[i], NULL);
    
    for (int x = 0; x< NUM_OF_THREADS; x++)
        if(validation[x] != 1)return 0;

    free(validation);
    free(tid);
    return 1;
}


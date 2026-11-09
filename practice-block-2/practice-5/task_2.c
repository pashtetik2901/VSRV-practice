#include <stdio.h>
#include <stdlib.h>

int main(){
    int column, row;

    printf("input count column: "); scanf("%d", &column);
    printf("input count row: "); scanf("%d", &row);

    if (row <= 0 || column <= 0){
        printf("error column or row <= 0");
        return 1;
    }

    int **matrix = (int **)malloc(sizeof(int *) * row);
    if (matrix == NULL){
        printf("\nerror with init row matrix");
        return 1;
    }

    for (int i = 0; i < row; i++){
        matrix[i] = (int *)malloc(sizeof(int) * column);
        
        if (matrix[i] == NULL){

            for(int j = 0; j < i; j++){
                free(matrix[j]);
            }

            free(matrix);
            
            printf("error with init column matrix");
            return 1;
        }
    }


    for (int i = 0; i < row; i++){
        printf("%s", i == 0 ? "\n[" : "[");
        for (int j = 0; j < column; j++){
            matrix[i][j] = 5;

            printf("(value = %d, address = %p)%s", matrix[i][j], (void *)&(matrix[i][j]), j == column - 1 ? "" : ", ");
        }

        printf("%s", i == row - 1 ? "]\n" : "],\n");
    }



    for (int i = 0; i < row; i++){
        free(matrix[i]);
    }

    free(matrix);

    return 0;
}


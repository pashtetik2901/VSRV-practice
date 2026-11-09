#include <stdio.h>
#include <stdlib.h>

int main(){
    int size_arr;

    printf("input size array: ");
    scanf("%d", &size_arr);
    printf("\n");

    if (size_arr == 0){
        printf("error size = 0");
        return 1;
    }

    int *arr = (int *)malloc(sizeof(int) * size_arr);

    if (arr == NULL){
        printf("error array is NULL");
        return 1;
    }

    for (int i = 0; i < size_arr; i++){
        arr[i] = i + 1;
    }

    for (int i = 0; i < size_arr; i++){
        printf("element of array: %d, address = %p\n", arr[i], (void *)&arr[i]);
    }

    free(arr);

    return 0;

}
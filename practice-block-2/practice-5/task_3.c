#include <stdio.h>

int is_prime(int num);
void simple_number(int *arr, int len, int *result);

int main(){
    int arr[5] = {2, 3, 7, 66, 55};
    int result[2];

    simple_number(arr, 5, result);

    printf("count = %d, min number = %d", result[0], result[1]);

    return 0;
}

void simple_number(int *arr, int len, int *result){
    int count = 0;
    int min = 99999999;

    for (int i = 0; i < len; i++){
        if (is_prime(arr[i])){
            min = arr[i] < min ? arr[i] : min;
            count += 1;
        }
    }

    result[0] = count;
    result[1] = min;
}

int is_prime(int num){
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;

    for (int i = 3; i * i <= num; i += 2){
        if (num % i){
            return 0;
        }
    }

    return 1;

}
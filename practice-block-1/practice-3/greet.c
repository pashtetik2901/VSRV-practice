#include <stdio.h>

int main(){
	char message[50];
	printf("Input your name: ");
	scanf("%49s", message);
	printf("Hello %s\n", message);

	return 0;
}

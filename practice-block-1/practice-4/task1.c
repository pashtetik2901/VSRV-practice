#include <stdio.h>
#include <unistd.h>

#define MAX_COUNT 10

void ChildProcess(void);
void ParentProcess(void);

int main(){
	int pid;

	pid = fork();

	if (pid < 0){
		printf("errow with pid");
		return 1;
	}

	else if (pid == 0){
		ChildProcess();
	}
	else{
		ParentProcess();
	}

	return 0;
}

void ChildProcess(void){	
	for (int i = 0; i < MAX_COUNT; i++){
		sleep(0.1);
		printf("   This line is from child, value = %d\n", i);
	}
}

void ParentProcess(void){
	for (int i = 0; i < MAX_COUNT; i++){
		printf("This line is from parent, value = %d\n", i);
	}
}

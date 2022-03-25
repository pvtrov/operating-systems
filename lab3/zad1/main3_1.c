//
// Created by mirabelka on 3/25/22.
//

#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>

void createNewProcess(int numberOfProcess, int counter){
    if (counter <= numberOfProcess-1){
        pid_t child_pid;
        child_pid = fork();
        if(child_pid != 0){
            printf("Parent number %d : Parent's PID: %d\n", counter, (int)getpid());
            printf("Parent number %d: Child's PID: %d\n", counter, (int)child_pid);
        } else {
            printf("Child number %d : Parent's PID: %d\n", counter+1, (int)getppid());
            printf("Child number %d: Child's PID: %d\n", counter+1, (int)getpid());
        }
        createNewProcess(numberOfProcess, counter+1);
    }else{
        exit(0);
    }
}

int main(int argc, char** argv){
    char* processesNumberInString;
    int processesNumber;

    if (argc <= 1){
        processesNumberInString = calloc(256, sizeof(char));
        printf("Give me number of processes you want to create ");
        scanf("%s", processesNumberInString);
        processesNumber = atoi(processesNumberInString);
    } else {
        processesNumber = atoi(argv[1]);
    }
    printf("main program PID: %d\n", (int)getpid());
    createNewProcess(processesNumber, 0);
    return 0;
}
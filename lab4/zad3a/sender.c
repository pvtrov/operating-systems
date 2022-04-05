//
// Created by mirabelka on 4/5/22.
//

#include <stdio.h>
#include <bits/types/siginfo_t.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


int caught = 0;
int to_send;
char* mode;

void first_handler(int sig, siginfo_t *info, void *ucontext){
    caught ++;
    if (strcmp(mode, "queue") == 0){
        printf("\n first handler: New SIGUSR1 caught. \n");
        printf("Number of signal caught and sent back from catcher is [%d].\n", info->si_value.sival_int);
    }
}

void second_handler(int sig){
    printf("\n ~~~~~~~~all signals sent back~~~~~~~~");
    printf("\nsecond handler: SIGUSR2 caught");
    printf("\n sender caught [%d] SIGUSR signals, should have caught [%d]. \n", caught, to_send);
    printf("second handler is disappearing\n");
    exit(0);
}


int main(int argc, char** argv){
    if (argc != 4){
        printf("\n i wanted 3 arguments! \n");
        exit(-1);
    }
    int catcher_PID = atoi(argv[1]);
    to_send = atoi(argv[2]);
    mode = argv[3];

    printf("\n hi im sender, my PID is %d\n", getpid());
    printf("catcher PID: %d\n", catcher_PID);
    printf("signals to send: %d\n", to_send);
    printf("mode: %s\n", mode);

    struct sigaction sig_SIGUSR1;
    sigemptyset(&sig_SIGUSR1.sa_mask);
    sig_SIGUSR1.sa_flags = SA_SIGINFO;
    sig_SIGUSR1.sa_sigaction = first_handler;
    if (strcmp(mode,"sigrt") != 0)
        sigaction(SIGUSR1, &sig_SIGUSR1, NULL);
    else
        sigaction(SIGRTMIN + 1, &sig_SIGUSR1, NULL);


    struct sigaction sig_SIGUSR2;
    sigemptyset(&sig_SIGUSR2.sa_mask);
    sig_SIGUSR2.sa_handler = second_handler;
    if (strcmp(mode,"sigrt") != 0)
        sigaction(SIGUSR2, &sig_SIGUSR2, NULL);
    else
        sigaction(SIGRTMIN + 2, &sig_SIGUSR2, NULL);


    printf("\n sender will be sending %d signals .... \n", to_send);
    for (int i = 0; i < to_send; i++) {
        printf("Sending SIGUSR1 %d...\n", i + 1);
        if (strcmp(mode, "kill") == 0) {
            kill(catcher_PID, SIGUSR1);
        }else if (strcmp(mode, "queue") == 0) {
            union sigval value;
            sigqueue(catcher_PID, SIGUSR1, value);
        }else if (strcmp(mode, "sigrt") == 0) {
            kill(catcher_PID, SIGRTMIN + 1);
        }else {
            printf("Wrong mode\n");
            return -1;
        }
    }


    printf("sender sent all [%d] SIGUSR1 signals. \n\n", to_send);
    if (strcmp(mode, "kill") == 0) {
        kill(catcher_PID, SIGUSR2);
    }else if (strcmp(mode, "queue") == 0) {
        union sigval value;
        sigqueue(catcher_PID, SIGUSR2, value);
    }else if (strcmp(mode, "sigrt") == 0) {
        kill(catcher_PID, SIGRTMIN + 2);
    }    else {
        printf("Wrong mode\n");
        return -1;
    }
    while(1){}

}

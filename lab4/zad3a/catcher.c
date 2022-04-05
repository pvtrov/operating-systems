//
// Created by mirabelka on 4/5/22.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

int caught = 0;
char* mode;

void handler1(int sig){
    caught++;
}

void handler2(int sig, siginfo_t *info, void *ucontext){
    printf("~~~~~~~~all signals sent~~~~~~~~\n\n");
    printf("catcher received SIGUSR2, now is going to send back [%d] received SIGUSR1 signals.\n", caught);

    pid_t sender_PID = info->si_pid;
    for (int i = 0; i < caught; i++){
        printf("sending back SIGUSR1 %d...\n", i + 1);
        if (strcmp(mode,"kill") == 0){
            kill(sender_PID, SIGUSR1);
        }
        else if (strcmp(mode,"queue") == 0){
            union sigval val;
            val.sival_int = i;
            sigqueue(sender_PID, SIGUSR1, val);
        }
        else if (strcmp(mode,"sigrt") == 0){
            kill(sender_PID, SIGRTMIN+1);
        }
        else{
            printf("Wrong mode\n");
        }
    }

    if (strcmp(mode,"kill") == 0){
        kill(sender_PID, SIGUSR2);
    }else if (strcmp(mode,"queue") == 0){
        union sigval value;
        sigqueue(sender_PID, SIGUSR2, value);
    }else if (strcmp(mode,"sigrt") == 0){
        kill(sender_PID, SIGRTMIN+2);
    }else{
        printf("something is wrong with the mode\n");
    }
    exit(0);
}


int main(int argc, char* argv[]) {

    if (argc != 2){
        printf("i wanted more arguments!\n");
        return -1;
    }

    printf("\n\n hi im catcher,  my is PID: %d\n", getpid());

    mode = argv[1];
    printf("mode: %s\n", mode);

    printf("catcher waiting for SIGUSR1...\n");



    struct sigaction act_SIGUSR1;
    sigemptyset(&act_SIGUSR1.sa_mask);
    act_SIGUSR1.sa_handler = handler1;
    if (strcmp(mode,"sigrt") != 0)
        sigaction(SIGUSR1, &act_SIGUSR1, NULL);
    else
        sigaction(SIGRTMIN + 1, &act_SIGUSR1, NULL);


    struct sigaction act_SIGUSR2;
    sigemptyset(&act_SIGUSR2.sa_mask);
    act_SIGUSR2.sa_flags = SA_SIGINFO;
    act_SIGUSR2.sa_sigaction  = handler2;
    if (strcmp(mode,"sigrt") != 0)
        sigaction(SIGUSR2, &act_SIGUSR2, NULL);
    else
        sigaction(SIGRTMIN + 2, &act_SIGUSR2, NULL);



    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGUSR1);
    sigdelset(&mask, SIGUSR2);
    if(strcmp(mode, "sigrt") == 0){
        sigdelset(&mask, SIGRTMIN+1);
        sigdelset(&mask, SIGRTMIN+2);
    }
    sigprocmask(SIG_SETMASK, &mask, NULL);


    while(1){
        sigsuspend(&mask);
    }

}
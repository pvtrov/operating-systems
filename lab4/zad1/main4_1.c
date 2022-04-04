//
// Created by mirabelka on 4/4/22.
//

#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include "stdio.h"


int which_mode(char* mode_text){
    if (strcmp(mode_text, "ignore") == 0){
        return 0;
    } else if (strcmp(mode_text, "handler") == 0){
        return 1;
    } else if (strcmp(mode_text, "pending") == 0){
        return 2;
    } else if (strcmp(mode_text, "mask") == 0){
        return 3;
    }
    return 4;
}

void raiseSignal(){
    raise(SIGUSR1);
    pid_t pid = fork();
    if (pid == 0){
        printf("Raising child signal \n");
        raise(SIGUSR1);
    }
    else{
        wait(NULL);
    }
}

void handler(int sigint){
    printf("SIGUSR1 received\n");
}

void pending(int sig){
    sigset_t set;
    if(sigpending(&set) == -1){
        fprintf(stderr, "Pending signals could not be obtained: %s\n", strerror(errno));
        exit(1);
    }
    if (sigismember(&set, sig)){
        printf("signal %d is pending\n", sig);
    }else{
        printf("signal %d is not pending\n", sig);
    }
}

void mask(int sig){
    sigset_t new_mask;
    sigemptyset(&new_mask);
    sigaddset(SIG_BLOCK, sig);
    if (sigprocmask(SIG_BLOCK, &new_mask, NULL) < 0){
        fprintf(stderr, "Signal could not be blocked: %s\n", strerror(errno));
        exit(1);
    }
}


int main(int argc, char** argv){
    if (argc <= 1){
        printf("give me more arguments");
        exit(1);
    }

    int sig = SIGUSR1;
    char* mode_text = argv[1];
    int mode = which_mode(mode_text);
    switch (mode) {
        case 0:         // ignore
            signal(SIGUSR1, SIG_IGN);
            raiseSignal();
        case 1:         // handler
            signal(SIGUSR1, handler);
            raiseSignal();
        case 2:         // pending
            pending(SIGUSR1);
        case 3:         // mask
            mask(SIGUSR1);
    }

    #ifdef FORK
    pid_t kid;
    if ((kid = fork()) == -1){
        fprintf(stderr, "cannot make a child: %s \n", strerror(errno));
    }else if (kid == 0){
        if (mode == 2){
            pending(SIGUSR1);
        }else{
            raise(SIGUSR1);
        }
        printf ("forked sucesfully\n");
        exit(0);
    }
    #endif

    #ifdef EXEC
    execl(argv[0], "exec_test", argv[1], NULL);
    #endif
    return 0;
}
//
// Created by mirabelka on 4/4/22.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void handler(int sig, siginfo_t *info, void *ucontext) {
    printf("Received signal number %d from a process with PID %d. Additional info:\n", info->si_signo, (int)info->si_pid);
    printf("    Real user ID of sending process: %d\n", (int)info->si_uid);
    printf("    User time consumed: %lf\n", (double)info->si_utime/sysconf(_SC_CLK_TCK));
    printf("    An errno value: %d\n\n", (int)info->si_errno);
}

void first_case(){
    struct sigaction case1;
    case1.sa_flags = SA_SIGINFO;
    case1.sa_sigaction = handler;
    sigemptyset(&case1.sa_mask);

    if (sigaction(SIGUSR1, &case1, NULL) == -1 || sigaction(SIGUSR2, &case1, NULL) == -1 || sigaction(SIGRTMIN, &case1, NULL) == -1){
        exit(1);
    }
    printf("first case test\n");
    raise(SIGUSR1);
    raise(SIGUSR2);
    raise(SIGRTMIN);
}

void second_case(){
    struct sigaction case2;
    case2.sa_flags = SA_NOCLDSTOP;
    case2.sa_sigaction = handler;
    sigemptyset(&case2.sa_mask);

    if (sigaction(SIGUSR1, &case2, NULL) == -1){
        exit(1);
    }
    printf("second case test\n");
    pid_t kid;
    kid = fork();
    if (kid == 0) {
        raise(SIGSTOP);
    }
    sleep(2);
    raise(SIGUSR1);
    }

void third_case(){
    struct sigaction case3;
    case3.sa_flags = SA_RESETHAND;
    case3.sa_sigaction = handler;
    sigemptyset(&case3.sa_mask);

    if (sigaction(SIGUSR1, &case3, NULL) == -1){
        exit(1);
    }
    printf("third case test\n");
    raise(SIGUSR1);
}

int main(int argc, char* argv[]){
    first_case();
    second_case();
    third_case();
    return 0;

 }
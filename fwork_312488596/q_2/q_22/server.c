// Server side!

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//#include <zconf.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int count=0;

void SIGINT_signal_handler(int signum){
        count++;
}

void SIGUSR1_signal_handler(int signum){
        printf("The number of SIGINT signals is %d", count);
}

int main(int argc, char **argv) {
    int relevant_pid;
    int status;

    printf("The pid is: %d\n", getpid());

    while(1){
        if(signal(SIGINT, SIGINT_signal_handler)== SIG_ERR){
            printf("cannot catch SIGUSR1");
        }

        if(signal(SIGUSR1, SIGUSR1_signal_handler)== SIG_ERR){
            printf("cannot catch SIGUSR1");
        }

    }
    
//    for (j = 0; j < numSigs; j++) {
//        sv.sival_int = sigData + j;
//        if (sigqueue(getLong(argv[1], 0, "pid"), sig, sv) == -1)
//            errExit("sigqueue %d", j);

        return 0;
    }
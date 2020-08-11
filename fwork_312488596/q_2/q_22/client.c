#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main(int argc, char **argv) {
    int relevant_pid, signal_type;
    int status, i;
    int num_signals_to_send = 1;

    // Check the integrity of the input
    if (argc < 4) {
        printf("Error: you need to pass server pid number, signal number and amount of signals you want to send.\n");
        exit(1);
    }

    relevant_pid = atoi(argv[1]);
    signal_type = atoi(argv[2]);

    if (signal_type == SIGINT) {
        num_signals_to_send = atoi(argv[3]);
        for (i = 0; i < num_signals_to_send; i++) {
            if ((status = kill(relevant_pid, SIGINT)) == -1)
                printf("ERROR: sending signal SIGINT failed for pid = %d.\n", relevant_pid);
        }
    } else if (signal_type == SIGUSR1) {
        if((status = kill(relevant_pid, SIGUSR1)) == -1)
            printf("ERROR: sending signal SIGUSR1 failed for pid = %d.\n", relevant_pid);
    }

    if (status) {
        switch (errno) {
            case EINVAL:
                printf("An invalid signal was specified.\n");
                break;
            case EPERM:
                printf("Process %d exists but we have no permission.\n", relevant_pid);
                break;
            case ESRCH:
                printf("Process %d does not exist.\n", relevant_pid);
                break;
        }
    } else {
        printf("Process %d exists.\n", relevant_pid);
    }

    return 0;
}
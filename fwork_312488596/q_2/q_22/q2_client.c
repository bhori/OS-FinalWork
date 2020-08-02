// Client side!

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main(int argc, char **argv) {
    int relevant_pid, signal_type;
    int status, i;
    int num_signals_to_send = 1;

    // TODO: fix the tiny bug when not transfering arguemnts to the main program
    if (argc < 2) {
        printf("Error you need to pass pid number\n");
        exit(1);
    }

    relevant_pid = atoi(argv[1]);
    signal_type = atoi(argv[2]);
    // printf("pid = %d\n", relevant_pid);

    if (signal_type == SIGINT) {

        printf("argc  = %d\n", argc);

        //TODO: Please check this case:
        if (argc < 4)
            num_signals_to_send = 1;
        else
            num_signals_to_send = atoi(argv[3]);

        for (i = 0; i < num_signals_to_send; i++) {
            printf("%d) Sending... \n", i);
            if (status = kill(relevant_pid, SIGINT) == -1)
                printf("ERROR: sending signal SIGINT failed for pid = %d failed.\n", relevant_pid);
        }

    } else if (signal_type == SIGUSR1) {
        status = kill(relevant_pid, SIGUSR1) == -1;
        if (status)
            printf("Error sending signal of type  = %d. \n", signal_type);
    }


//    if (status = kill(relevant_pid, SIGUSR1) == -1)
//        printf("sending signal SIGUSR1 failed for pid = %d\n", relevant_pid);

    //printf("res = %d\n", status);

    if (status) {
        switch (errno) {
            case EINVAL:
                printf("An invalid signal was specified.\n");
                break;
            case EPERM:
                printf("The process does not have permission to send the signal to any of the target processes.\n");
                break;
            case ESRCH:
                printf("The pid or process group does not exist.\n");
                break;
        }
    } else {
        printf("Process %d exists.\n", relevant_pid);
    }


    return 0;
}
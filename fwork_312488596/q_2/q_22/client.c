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
    if (argc < 2) {
        printf("Error: you need to pass pid number\n");
        exit(1);
    }

    relevant_pid = atoi(argv[1]);
    signal_type = atoi(argv[2]);

    if (signal_type == SIGINT) {
        //TODO: Please check this case:
        if (argc < 4)
            num_signals_to_send = 1;
        else
            num_signals_to_send = atoi(argv[3]);

        for (i = 0; i < num_signals_to_send; i++) {
            if ((status = kill(relevant_pid, SIGINT)) == -1)
                printf("ERROR: sending signal SIGINT failed for pid = %d failed.\n", relevant_pid);
        }

    } else if (signal_type == SIGUSR1) {
        status = kill(relevant_pid, SIGUSR1) == -1;
        if (status)
            printf("Error sending signal of type  = %d. \n", signal_type);
    }

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


/*// Client side!

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main(int argc, char **argv) {
    int relevant_pid;
    int signal_type;
    int num;
    int status;

    if (argc < 2) {
        printf("Error: you need to pass pid number\n");
        exit(1);
    }

    relevant_pid = atoi(argv[1]);
    // printf("pid = %d\n", relevant_pid);
    signal_type = atoi(argv[2]);
    if(signal_type==2){
        num = atoi(argv[3]);
        int i;
        for(i=1; i<=num; i++){
            if (status = kill(relevant_pid, SIGINT) == -1)
                printf("sending signal SIGINT failed for pid = %d\n", relevant_pid);
        }
    }

    if(signal_type==10){
        //num = atoi(argv[3]);
        if (status = kill(relevant_pid, SIGUSR1) == -1)
                printf("sending signal SIGINT failed for pid = %d\n", relevant_pid);
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
    }
    else{
        printf("Process %d exists.\n", relevant_pid);
    }


        return 0;
    }*/
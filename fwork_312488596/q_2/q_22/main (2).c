// Client side!

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main(int argc, char **argv) {
    int relevant_pid;
    int status;

    // TODO: fix the tiny bug when not transfering arguemnts to the main program
    if (argc < 1) {
        printf("Error you need to pass pid number\n");
        exit(1);
    }

    relevant_pid = atoi(argv[1]);
    // printf("pid = %d\n", relevant_pid);


    if (status = kill(relevant_pid, SIGINT) == -1)
        printf("sending signal SIGINT failed for pid = %d\n", relevant_pid);

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
    }
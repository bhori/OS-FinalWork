#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv) {
    int relevant_pid;
    int status;

    //Check the integrity of the input
    if (argc < 2) {
        printf("Error: you need to pass pid number\n");
        exit(1);
    }

    relevant_pid = atoi(argv[1]);

    if (status = kill(relevant_pid, 0) == -1)
        printf("sending signal failed for pid = %d\n", relevant_pid);

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
    }
    else{
        printf("Process %d exists.\n", relevant_pid);
    }


    return 0;
}
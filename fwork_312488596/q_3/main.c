#include <sched.h>
#include <stdio.h>
#include <stdlib.h>

#define SCHED_IDLE        5

int
main(int argc, char *argv[]) {
    int j, pol;
    struct sched_param sp;

    for (j = 1; j < argc; j++) {
        printf("j = %d\n", j);
        pol = sched_getscheduler(atoi(argv[1]));
        if (pol == -1)
            printf("ERROR: sched_getscheduler\n");

        if (sched_getparam(atoi(argv[j]), &sp) == -1)
            printf("ERROR: sched_getparam\\n");

        printf("%s: %-5s ", argv[j],
               (pol == SCHED_OTHER) ? "OTHER" :
               (pol == SCHED_RR) ? "RR" :
               (pol == SCHED_FIFO) ? "FIFO" :
               (pol == SCHED_IDLE) ? "IDLE" : "???");
        printf("%2d\n", sp.sched_priority);
    }

    exit(EXIT_SUCCESS);
}

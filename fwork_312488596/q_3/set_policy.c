// cat /sys/block/sda/queue/scheduler

#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SCHED_DEADLINE        6
#define SCHED_IDLE        5

int main(int argc, char **argv) {
    int nice_value, relevant_policy, priority;
    struct sched_param sp;

    int pol;
    struct sched_param sp2;

    //    printf("j = %d\n", j);
        pol = sched_getscheduler(0);
        if (pol == -1)
            printf("ERROR: sched_getscheduler\n");

        if (sched_getparam(0, &sp2) == -1)
            printf("ERROR: sched_getparam\\n");

        printf("The policy and priority before the change: policy - %-5s, priority - ", 
               (pol == SCHED_OTHER) ? "OTHER" :
               (pol == SCHED_RR) ? "RR" :
               (pol == SCHED_FIFO) ? "FIFO" :
               (pol == SCHED_IDLE) ? "IDLE" : "???");
        printf("%2d\n", sp2.sched_priority);
    

    relevant_policy = atoi(argv[1]);
    priority = atoi(argv[2]);
    switch (relevant_policy) {
        case SCHED_DEADLINE:
        case SCHED_FIFO: {
            printf("Schedualer of type: %d\n", relevant_policy);
            if(priority<=0){
                printf("Wrong input, invalid priority!\n");
                return (1);
            }
            sp.sched_priority = priority;
            break;
        }
        case SCHED_IDLE: {
            printf("Schedualer of type: %d\n", relevant_policy);
            if(priority!=0){
                printf("Wrong input, invalid priority!\n");
                return (1);
            }
            sp.sched_priority = priority;
            break;
        }
        case SCHED_RR: {
            printf("Schedualer of type: %d\n", relevant_policy);
            if(priority<=0){
                printf("Wrong input, invalid priority!\n");
                return (1);
            }
            sp.sched_priority = priority;
            break;
        }
        case SCHED_OTHER: {
            printf("Schedualer of type: %d\n", relevant_policy);
            if(priority!=0){
                printf("Wrong input, invalid priority!\n");
                return (1);
            }
            sp.sched_priority = priority;
            break;
        }
        default: {
            printf("Wrong input, invalid policy!\n");
            return (1);
        }

    }

    // int pid=atoi(argv[3]);

    // TODO: Please ask the lecturer about pid = 0, is it always??
    // if (sched_setscheduler(pid, relevant_policy, &sp) == -1)
    if (sched_setscheduler(0, relevant_policy, &sp) == -1)
        printf("ERROR! sched_setscheduler\n");


    //    printf("j = %d\n", j);
        pol = sched_getscheduler(0);
        if (pol == -1)
            printf("ERROR: sched_getscheduler\n");

        if (sched_getparam(0, &sp2) == -1)
            printf("ERROR: sched_getparam\\n");

        printf("The policy and priority before the change: policy - %-5s, priority - ", 
               (pol == SCHED_OTHER) ? "OTHER" :
               (pol == SCHED_RR) ? "RR" :
               (pol == SCHED_FIFO) ? "FIFO" :
               (pol == SCHED_IDLE) ? "IDLE" : "???");
        printf("%2d\n", sp2.sched_priority);



    while(1);
    return 0;
}

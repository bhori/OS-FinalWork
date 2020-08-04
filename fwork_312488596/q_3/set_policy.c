// cat /sys/block/sda/queue/scheduler

#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// #define __USE_GNU
#define SCHED_DEADLINE        6
#define SCHED_IDLE        5


void get_Policy_Priority(char status){
    int pol;
    struct sched_param sp;

    pol = sched_getscheduler(0);
    if (pol == -1)
        printf("ERROR: sched_getscheduler\n");

    if (sched_getparam(0, &sp) == -1)
        printf("ERROR: sched_getparam\\n");

    if(status=='B'){
        printf("The policy and priority before the change: policy - %-5s, priority - ", 
            (pol == SCHED_OTHER) ? "OTHER" :
            (pol == SCHED_RR) ? "RR" :
            (pol == SCHED_FIFO) ? "FIFO" :
            (pol == SCHED_IDLE) ? "IDLE" : "???");
    }else if (status=='A'){
        printf("The policy and priority after the change: policy - %-5s, priority - ", 
            (pol == SCHED_OTHER) ? "OTHER" :
            (pol == SCHED_RR) ? "RR" :
            (pol == SCHED_FIFO) ? "FIFO" :
            (pol == SCHED_IDLE) ? "IDLE" : "???");
    }
    printf("%2d\n", sp.sched_priority);
}

int main(int argc, char **argv) {
    int nice_value, relevant_policy, priority;
    struct sched_param sp;

    //Check the integrity of the input
    if (argc < 3) {
        printf("Error: you need to pass policy and priority!\n");
        exit(1);
    }

    // int pol;
    // struct sched_param sp2;

    // pol = sched_getscheduler(0);
    // if (pol == -1)
    //     printf("ERROR: sched_getscheduler\n");

    // if (sched_getparam(0, &sp2) == -1)
    //     printf("ERROR: sched_getparam\\n");

    // printf("The policy and priority before the change: policy - %-5s, priority - ", 
    //         (pol == SCHED_OTHER) ? "OTHER" :
    //         (pol == SCHED_RR) ? "RR" :
    //         (pol == SCHED_FIFO) ? "FIFO" :
    //         (pol == SCHED_IDLE) ? "IDLE" : "???");
    // printf("%2d\n", sp2.sched_priority);

    // prints the policy and priority before the change
    get_Policy_Priority('B');

    relevant_policy = atoi(argv[1]);
    priority = atoi(argv[2]);
    switch (relevant_policy) {
        case SCHED_DEADLINE:{
            // printf("Schedualer of type: %d\n", relevant_policy);
            // if (sched_setattr(0, sa, 0) == -1)
            //     printf("ERROR! sched_setattr\n");
            // sp.sched_priority = priority;
            break;
        }
        case SCHED_FIFO: {
            printf("Schedualer of type: %d\n", relevant_policy);
            if(priority<=0){
                printf("Wrong input, invalid priority0 for policy of type SCHED_FIFO!\n");
                return (1);
            }
            sp.sched_priority = priority;
            break;
        }
        case SCHED_IDLE: {
            printf("Schedualer of type: %d\n", relevant_policy);
            if(priority!=0){
                printf("Wrong input, invalid priority for policy of type SCHED_IDLE!\n");
                return (1);
            }
            sp.sched_priority = priority;
            break;
        }
        case SCHED_RR: {
            printf("Schedualer of type: %d\n", relevant_policy);
            if(priority<=0){
                printf("Wrong input, invalid priority for policy of type SCHED_RR!\n");
                return (1);
            }
            sp.sched_priority = priority;
            break;
        }
        case SCHED_OTHER: {
            printf("Schedualer of type: %d\n", relevant_policy);
            if(priority!=0){
                printf("Wrong input, invalid priority for policy of type SCHED_OTHER!\n");
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

    // if (sched_setscheduler(pid, relevant_policy, &sp) == -1)
    if (sched_setscheduler(0, relevant_policy, &sp) == -1)
        printf("ERROR! sched_setscheduler\n");


    // pol = sched_getscheduler(0);
    // if (pol == -1)
    //     printf("ERROR: sched_getscheduler\n");

    // if (sched_getparam(0, &sp2) == -1)
    //     printf("ERROR: sched_getparam\\n");

    // printf("The policy and priority after the change: policy - %-5s, priority - ", 
    //         (pol == SCHED_OTHER) ? "OTHER" :
    //         (pol == SCHED_RR) ? "RR" :
    //         (pol == SCHED_FIFO) ? "FIFO" :
    //         (pol == SCHED_IDLE) ? "IDLE" : "???");
    // printf("%2d\n", sp2.sched_priority);

    // prints the policy and priority after the change
    get_Policy_Priority('A');

    while(1);

    return 0;
}

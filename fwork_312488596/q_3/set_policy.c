
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <linux/sched.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>

// prints the current scheduling policy and priority of the process, 'status' is an indicator that indicates whether the printing is done before or after the change.
void get_Policy_Priority(char status){
    int pol;
    struct sched_param sp;

    pol = sched_getscheduler(0);
    if (pol == -1)
        printf("ERROR: sched_getscheduler\n");

    if (sched_getparam(0, &sp) == -1)
        printf("ERROR: sched_getparam\\n");

    char * current_policy = (pol == SCHED_OTHER) ? "OTHER" :
            (pol == SCHED_RR) ? "RR" :
            (pol == SCHED_FIFO) ? "FIFO" :
            (pol == SCHED_IDLE) ? "IDLE" :
            (pol == SCHED_DEADLINE) ? "DEADLINE" : "???";

    // 'B' indicates that the print is before the change, 'A' indicates that the print is after the change.
    if(status=='B'){
        printf("The policy and priority before the change: policy - %-5s, priority - ", current_policy);
    }else if (status=='A'){
        printf("The policy and priority after the change: policy - %-5s, priority - ", current_policy); 
    }
    printf("%2d\n", sp.sched_priority);
}

// Redefinition of struct sched_attr
struct sched_attr {
    uint32_t size;

    uint32_t sched_policy;
    uint64_t sched_flags;

    /* SCHED_NORMAL, SCHED_BATCH */
    int32_t sched_nice;

    /* SCHED_FIFO, SCHED_RR */
    uint32_t sched_priority;

    /* SCHED_DEADLINE (nsec) */
    uint64_t sched_runtime;
    uint64_t sched_deadline;
    uint64_t sched_period;
};


// sched_setattr syscall wrapper
int sched_setattr(pid_t pid, const struct sched_attr *attr, unsigned int flags)
{
   return syscall(__NR_sched_setattr, pid, attr, flags);
}


int main(int argc, char **argv) {
    int relevant_policy, priority;
    struct sched_param sp;

    //Check the integrity of the input
    if (argc < 3) {
        printf("Error: you need to pass policy and priority!\n");
        exit(1);
    }

    // prints the policy and priority before the change
    get_Policy_Priority('B');

    relevant_policy = atoi(argv[1]);
    priority = atoi(argv[2]);
    
    switch (relevant_policy) {
        case SCHED_DEADLINE:{
            struct sched_attr attr = {
            .size = sizeof(attr),
            .sched_policy = SCHED_DEADLINE,
            .sched_runtime = 30000000,
            .sched_period = 100000000,
            .sched_deadline = 100000000
            };

            if (sched_setattr(0, &attr, 0))
                perror("sched_setattr()");
            break;
        }
        case SCHED_FIFO: {
            printf("Schedualer of type: %d\n", relevant_policy);
            if(priority<=0 || priority>=100){
                printf("Wrong input, invalid priority for policy of type SCHED_FIFO!\n");
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
            if(priority<=0 || priority>=100){
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

    // if relevant_policy is SCHED_DEADLINE the change has already been made above!
    if(relevant_policy!=SCHED_DEADLINE){
        if (sched_setscheduler(0, relevant_policy, &sp) == -1)
            printf("ERROR! sched_setscheduler\n");
    }

    // prints the policy and priority after the change
    get_Policy_Priority('A');

    // while(1);

    // Delays the end of the program to allow you to check the scheduling policy and priority with certain commands (e.g. chrt -p <pid>)
    sleep(30);

    return 0;
}

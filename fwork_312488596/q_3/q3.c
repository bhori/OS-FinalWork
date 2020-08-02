// cat /sys/block/sda/queue/scheduler

#include <stdio.h>
#include <sched.h>
#include <stdlib.h>

#define SCHED_DEADLINE        6
#define SCHED_IDLE        5

int main(int argc, char **argv) {
    int nice_value, relevant_policy;
    struct sched_param sp;

    relevant_policy = atoi(argv[1]);
    switch (relevant_policy) {
        case SCHED_DEADLINE:
        case SCHED_FIFO:
        case SCHED_IDLE:
        case SCHED_RR:
        case SCHED_OTHER: {
            printf("Schedualer of type: %d\n", relevant_policy);
            sp.sched_priority = atoi(argv[2]);
            break;
        }
        default: {
            printf("Wrong input, invalid policy!");
            return (1);
        }

    }

    // TODO: Please ask the lecturer about pid = 0, is it always??
    if (sched_setscheduler(0, relevant_policy, &sp) == -1)
        printf("ERROR! sched_setscheduler");

    return 0;
}

In order to run the program you need to run the command 'make' or 'make set_policy' that will compile the program 'set_policy.c' and call the executable file 'set_policy'.
You then need to run the program name with 2 more parameters (integers) separated by a space when the first parameter indicates the required policy and the second parameter indicates the required priority.

* Note that in order to change the scheduling policy to SCHED_FIFO, SCHE_RR or SCHED_DEADLINE you need to run the program with sudo.
* I added a 'sleep' command at the end of the program for 30 seconds to allow you to check the scheduling policy of the process and its priority after the change made by the program.

Running example:
1) make
2) ./set_policy 5 0

** In order to clean the executable files and the compiled files you can run the command 'make clean'.
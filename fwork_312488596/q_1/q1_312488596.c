#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];            /* 1. uninitialized data segment-bss */ 
int primes[] = { 2, 3, 5, 7 };  /* 2. initialized data segment */

static int
square(int x)                   /* 3. text segment */
{
   int result;                 /* 4. Where is allocated? 	** stack (maybe it is wrong because the function is static) */

    result = x * x;
   return result;              /* 5. How the return value is passed? */
}

static void
doCalc(int val)                 /* 6. text segment */
{
    printf("The square of %d is %d\n", val, square(val));
//printf("The square of %d is %d\n", val, 5);
    if (val < 1000) {
        int t;                  /* 7. Where is allocated? 	** stack (maybe it is wrong because the function is static) */

        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int
main(int argc, char* argv[])    /* text segment */
{
    static int key = 9973;      /* initialized data segment */
    static char mbuf[10240000]; /* uninitialized data segment-bss */
    char* p;                    /* Where is allocated? 		** stack */


    doCalc(key);

    exit(EXIT_SUCCESS);
}

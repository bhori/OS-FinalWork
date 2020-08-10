#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include <stdio.h>
#include <ftw.h>
#include <string.h>

/* Function called by nftw() */
static int dirTree(const char *pathname, const struct stat *sbuf, int type, struct FTW *ftwb) {

    if (type == FTW_NS) {
        printf("?");
    } else if(type != FTW_SL){
        switch (sbuf->st_mode & S_IFMT) {  /* Print file type */
            case S_IFREG:           /* Regular file.  */
                printf("F %ld %s\n", sbuf->st_ino, basename(pathname));
                 break; 
            case S_IFDIR:           /* Directory.  */
                printf("D %ld %s\n", sbuf->st_ino, basename(pathname));
                break; 
            default:            /* Irrelevant for our case */
                printf("?");
                break; 
        }
    }

    return 0;
}


int main(int argc, char **argv) {

    int flags = 0;

    // Check the integrity of the input
    if (argc < 2) {
        printf("Error, you should supply an argument.\n");
        return (-1);
    }

    // Turns on the flag that ignores the soft link files.
    flags |= FTW_PHYS;

    if (nftw(argv[1], dirTree, 30, flags) == -1) {
        printf("Something failed in nftw function.\n");
    }

    return 0;
}

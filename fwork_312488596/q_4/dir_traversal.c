#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include <stdio.h>
#include <ftw.h>
#include <string.h>

/* Function called by nftw() */
static int dirTree(const char *pathname, const struct stat *sbuf, int type, struct FTW *ftwb) {

    long inode = sbuf->st_ino;

    switch(type){        /* Print file type */
        case FTW_F:         /* Regular file.  */
            printf("F %ld %s\n", inode, basename(pathname));
            break;
        case FTW_D:         /* Directory.  */
            printf("D %ld %s\n", inode, basename(pathname));
            break;
        case FTW_DNR:       /* Directory which can't be read. */
            printf("DNR %ld %s\n", inode, basename(pathname));
            break;
        case FTW_NS:         /* Unstatable file */
            printf("NS %ld %s\n", inode, basename(pathname));
            break;
        case FTW_SL:         /* Igonre symbolic link */
            break;
        default:
            break;
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

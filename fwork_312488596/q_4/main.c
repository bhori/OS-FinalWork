#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <ftw.h>
#include <libgen.h>

/* Function called by nftw() */
static int dirTree(const char *pathname, const struct stat *sbuf, int type,
                   struct FTW *ftwb) {

    printf("pathname: %s\n", pathname);


    if (type == FTW_NS) {
        printf("?");
    } else {
        switch (sbuf->st_mode & S_IFMT) {  /* Print file type */
            case S_IFREG:
                printf("F %d %s\n", sbuf->st_ino, basename(pathname));
                break; /* Regular file.  */
            case S_IFDIR:
                printf("D %d %s\n", sbuf->st_ino, basename(pathname));
                break; /* Directory.  */
            case S_IFLNK:
                printf("l %d %s\n", sbuf->st_ino, basename(pathname));
                break; /* Symbolic link.  */
            default:
                printf("?");
                break; /* Irrelevant for our case */
        }
    }
}


int main(int argc, char **argv) {

    int flags = 0;
    if (argc < 2) {
        printf("Error, you should supply an argument.\n");
        return (-1);
    }

    printf("Focusing on directory: %s\n", argv[1]);

    //TODO: Figure out whats wrong!!
    flags |= FTW_CHDIR;
    flags |= FTW_PHYS;
    flags |= FTW_DEPTH;

    if (nftw(argv[1], dirTree, 30, flags) == -1) {
        printf("Something failed\n");
    }
    return 0;
}

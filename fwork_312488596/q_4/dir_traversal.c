#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <ftw.h>
#include <libgen.h>

/* Function called by nftw() */
static int dirTree(const char *pathname, const struct stat *sbuf, int type,
                   struct FTW *ftwb) {

    // printf("pathname: %s\n", pathname);


    if (type == FTW_NS) {
        printf("?");
    } else if(type != FTW_SL){
        // switch (sbuf->st_mode & S_IFMT) {  /* Print file type */
        //     case S_IFREG:           /* Regular file.  */
        //         printf("F %d %s\n", sbuf->st_ino, basename(pathname));
        //         // printf("F %d %s\n", sbuf->st_ino, ftwb->base);
        //         break; 
        //     case S_IFDIR:           /* Directory.  */
        //         printf("D %d %s\n", sbuf->st_ino, basename(pathname));
        //         // printf("D %d %s\n", sbuf->st_ino, ftwb->base);
        //         break; 
        //     case S_IFLNK:        /* Symbolic link.  */
        //         printf("l %d %s\n", sbuf->st_ino, basename(pathname));
        //         break;
        //     default:            /* Irrelevant for our case */
        //         printf("?");
        //         break; 
        // }
        switch (type) {  /* Print file type */
            case FTW_F:           /* Regular file.  */
                printf("F %ld %s\n", sbuf->st_ino, basename(pathname));
                // printf("F %ld %s\n", sbuf->st_ino, ftwb->base);
                break; 
            case FTW_D:           /* Directory.  */
                printf("D %ld %s\n", sbuf->st_ino, basename(pathname));
                // printf("D %d %s\n", sbuf->st_ino, ftwb->base);
                break; 
            case S_IFLNK:        /* Symbolic link.  */
                printf("l %ld %s\n", sbuf->st_ino, basename(pathname));
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
    if (argc < 2) {
        printf("Error, you should supply an argument.\n");
        return (-1);
    }

    printf("Focusing on directory: %s\n", argv[1]);

    //TODO: Figure out whats wrong!!
    // flags |= FTW_CHDIR;
    flags |= FTW_PHYS;
    // flags |= FTW_DEPTH;

    if (nftw(argv[1], dirTree, 30, flags) == -1) {
        printf("Something failed\n");
    }
    return 0;
}

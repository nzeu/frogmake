#include "frogmake.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv) {
    /* this will be used later to loop through data, 
     * number of values changed by parsefile() */
    int nval;
    int *pnval = &nval; 
    /* contains the contents of the frogm.toml */
    char **data;

    //segfaults, probably dosen't like null values
    data = parseFile(pnval);

    /* we call gcc here with the arguments */
    execvp("/usr/bin/gcc", data);
    perror("execv");
    exit(EXIT_FAILURE);

    free(data);
    printf("done\n");

    return 0;
}

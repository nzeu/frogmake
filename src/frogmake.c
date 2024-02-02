#include "frogmake.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv) {
    /* this will be used later to loop through data, 
     * number of values, later set by parsefile() */
    int nval;
    int *pnval = &nval; 
    /* contains the contents of the frogm.toml */
    char **data;

    data = parseFile(pnval);

    /* we call gcc here with the arguments */
    execvp("/usr/bin/gcc", data);
    perror("execv");
    exit(EXIT_FAILURE);

    free(data);

    return 0;
}

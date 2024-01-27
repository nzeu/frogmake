#ifndef PARSEFILE_H
#define PARSEFILE_H

/* get the data from the frogm.toml */
char **parseFile(int *nval);

/* form a string will all the data */
void concat(char *dest, char **src, int size);

#endif

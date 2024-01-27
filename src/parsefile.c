#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "toml.h"

char **parseFile(int *nval) {
    FILE *fp;
    char errbuff[200];
    char **data;

    //open the file
    fp = fopen("frogm.toml", "r");
    if (!fp) {
	perror("frogm.toml");
	fp = fopen("frogm.toml", "w");
	printf("frogm.toml file was not found and was created for you\n");
	fclose(fp);
	fp = fopen("frogm.toml", "r");
    }
    printf("opened\n");

    //get the file toml data stored in conf
    toml_table_t* conf = toml_parse_file(fp, errbuff, sizeof(errbuff));
    printf("parsed\n");
    fclose(fp);
    printf("closed\n");	

    if (!conf) {
	printf("cannot parse frogm.toml\n");
	exit(1);
    }

    /*******************************************************
     * find tables from here
     */
    
    toml_table_t* build = toml_table_in(conf, "build");
    if (!build) {
	fprintf(stderr, "build table missing. Exiting with error code 1\n");
	exit(1);
    }

    toml_table_t* files = toml_table_in(conf, "files");
    if (!files) {
	fprintf(stderr, "files table missing. Exiting with error code 1.\n");
	exit(1);
    }
    printf("tables found\n");

    /********************************************************
     *  find values from here, FREE ALL STRINGS AFTER USE
     */  
    //name will be stored at [1]
    toml_datum_t name = toml_string_in(build, "name");
    //take into account the "-o" added later on
    *nval += 2;

    //the files will be stored after name
    toml_array_t* src = toml_array_in(files, "src");
    if (src != NULL){
	*nval += toml_array_nelem(src);
    }

    //the last one should be equal to NULL 
    data = malloc((*nval * sizeof(char*)) + 1);

    /********************************************************
     * add elements to data from here
     */
    
    //NULL
    data[*nval+1] = NULL;
    //gcc
    data[0] = malloc(3);
    strcpy(data[0], "gcc");
    //to be put before name in the args
    data[1] = malloc(2);
    strcpy(data[1], "-o");
    if (!name.ok) {
	//free name.u.s, allocate enough for a.out 
	data[2] = malloc(6);
	strcpy(data[2], "a.out");
	free(name.u.s);
	fprintf(stderr, "No name found, defaulted to a.out");
    }else {
	//put name.u.s in data[1]
	data[2] = malloc(sizeof(name.u.s));
	strcpy(data[2], name.u.s);
	free(name.u.s);
    }

    if (!src) {
	//free src, data, and conf before exiting with error code 1
	free(data);
	fprintf(stderr, "ERROR: missing src files in frogm.toml");
	exit(1);
    }else {
	for (int i = 0; i < toml_array_nelem(src); i++) {
	    printf("first time looping%i\n", i);
	    char *tmp = toml_string_at(src, i).u.s;
	    data[i+3] = malloc(sizeof(tmp));
	    strcpy(data[i+3], tmp);
	    free(tmp);
	    printf("finished loop\n");
	}
    }

    printf("allacated\n");
    printf("%s %s %s %s %s\n", data[0], data[1], data[2], data[3], data[4]);

    free(conf);

    printf("does it reach\n");

    return data;
}


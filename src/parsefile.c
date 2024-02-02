#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "toml.h"

char **parseFile(int *nval) {
    FILE *fp;
    char errbuff[200];
    char **data;

    //open the file and and do stuff in case it's not there
    fp = fopen("frogm.toml", "r");
    if (!fp) {
	perror("frogm.toml");
	fprintf(stderr, "frogm.toml not found, one can be create for you (y/n) ");
	char yn;
	scanf("%s", &yn);
	switch (yn) {
	    case 'y':
		fp = fopen("frogm.toml", "w");
		fclose(fp);
		fprintf(stderr, "A file was created.\n");
		exit(EXIT_FAILURE);
	    case 'n':
		fprintf(stderr, "No file was created.\n");
		exit(EXIT_FAILURE);
	    default:
		fprintf(stderr, "Invalid input, no file will be created.\n");
		exit(EXIT_FAILURE);
	}
    }

    //get the file toml data stored in conf
    toml_table_t* conf = toml_parse_file(fp, errbuff, sizeof(errbuff));
    fclose(fp);

    if (!conf) {
	printf("cannot parse frogm.toml\n");
	exit(1);
    }

    /*******************************************************
     * find tables from here
     */
    
    toml_table_t* headers = toml_table_in(conf, "headers");

    /********************************************************
     *  find values from here, FREE ALL STRINGS AFTER USE
     */  
    //name will be stored at [1]
    toml_datum_t name = toml_string_in(conf, "name");
    //take into account the "-o" added later on
    *nval += 2;

    //the source files will go after the headers 
    toml_array_t* src = toml_array_in(conf, "src");
    if (src != NULL){
	*nval += toml_array_nelem(src);
    }else {
	fprintf(stderr, "no src array given. Exiting with error code 1.\n");
	toml_free(conf);
	exit(EXIT_FAILURE);
    }
    
    /* get nval to the right number */
    if (headers != NULL) {
	/* check if all the elements in headers are arrays */
	if (toml_table_nkval(headers) > toml_table_narr(headers)) {
	    fprintf(stderr, "ERROR: non array elements found in headers, exiting with code 1\n");
	    exit(EXIT_FAILURE);
	}
	//loop through the table to add to nval
	for (int i = 0; i < toml_table_narr(headers); i++) {
	    //2 for the dir name + the number of elem in the array
	    *nval += toml_array_nelem(toml_array_nokey(headers, i)) + 2;
	}
    }

    //the last one should be equal to NULL, the + 1
    data = malloc((*nval * sizeof(char*)) + 1);

    const int INDEX_OF_GCC = 0;
    const int INDEX_OF_NAMEF = 1;
    const int INDEX_OF_NAME = 2;
    int INDEX_OF_HEADERS = INDEX_OF_NAME+1;

    /********************************************************
     * add elements to data from here
     */
    
    /* the standard gcc and -o */
    data[INDEX_OF_GCC] = malloc(3);
    strcpy(data[INDEX_OF_GCC], "gcc");
    data[INDEX_OF_NAMEF] = malloc(2);
    strcpy(data[INDEX_OF_NAMEF], "-o");

    /* name */
    if (!name.ok) {
	//free name.u.s, allocate enough for a.out 
	data[INDEX_OF_NAME] = malloc(6);
	strcpy(data[INDEX_OF_NAME], "a.out");
	free(name.u.s);
	fprintf(stderr, "No name found, defaulted to a.out");
    }else {
	//put name.u.s in data[1]
	data[INDEX_OF_NAME] = malloc(sizeof(name.u.s));
	strcpy(data[INDEX_OF_NAME], name.u.s);
	free(name.u.s);
    }

    /* manage header files and directories somehow 
     * well ackchully just use a headers table,
     * an array for each dir, get 'em with index and
     * get also the key for the dir name, elements of the
     * arr are the files
     */
    for (int i = 0; i < toml_table_narr(headers); i++) {
	//-iquote
	data[INDEX_OF_HEADERS] = malloc(7);
	strcpy(data[INDEX_OF_HEADERS], "-iquote");
	INDEX_OF_HEADERS++;
	data[INDEX_OF_HEADERS] = malloc(sizeof(toml_key_in(headers, i)));
	strcpy(data[INDEX_OF_HEADERS], toml_key_in(headers, i));
	INDEX_OF_HEADERS++;
	toml_array_t *arr = toml_array_nokey(headers, i);
	for (int j = 0; j < toml_array_nelem(arr); j++) {
	    toml_datum_t str = toml_string_at(arr, j);
	    data[INDEX_OF_HEADERS] = malloc(sizeof(toml_string_at(arr, j).u.s));
	    strcpy(data[INDEX_OF_HEADERS], toml_string_at(arr, j).u.s); 
	    INDEX_OF_HEADERS++;
	    free(str.u.s);
	}
    }
     
    /* source files from here */
    for (int i = 0; i < toml_array_nelem(src); i++) {
	char *tmp = toml_string_at(src, i).u.s;
	data[INDEX_OF_HEADERS] = malloc(sizeof(tmp));
	strcpy(data[INDEX_OF_HEADERS], tmp);
	INDEX_OF_HEADERS++;
	free(tmp);
    }

    printf("%s \n", data[0]);
    for (int i = 0; i < *nval; i++) {
	printf("%s ", data[i]);
    }
    printf("\n");

    free(conf);

    return data;
}

#include "question6.h"
#include <string.h>
#include <stddef.h>

void parse_arguments(char *buffer, char **argv){
    int i = 0;

    //the first word
    argv[i]=strtok(buffer," \t");

    // the next words , word by word
    while (argv[i] != NULL && i < MAX_ARGS - 1) {
        i++;
        argv[i] = strtok(NULL, " \t");
    }

    argv[i] =  NULL;
}
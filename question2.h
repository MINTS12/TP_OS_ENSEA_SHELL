#ifndef QUESTION_2_H
#define QUESTION_2_H

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

// constant for the buffer
#define MAX_CMD_SIZE 1024
#define ERROR_FORK "Error: fork failed\n"

void execute_one_simple_command(char *buffer);

#endif
#ifndef QUESTION_4_H
#define QUESTION_4_H

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h> 


#define MAX_STATUS_SIZE 180



void show_status_prompt(int status, long period_ms);

#endif
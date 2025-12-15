#include "question4.h"

void show_status_prompt(int status , long period_ms) {
    char buffer[MAX_STATUS_SIZE];
    int len ;
    // when the commande finished normally (enseash [exit:0] %)
    if (WIFEXITED(status)) {

        int exit_code = WEXITSTATUS(status);

        len = snprintf(buffer,MAX_STATUS_SIZE,  "enseash [exit:%d|%ldms] %% ", exit_code , period_ms);
    } 
    //when the commande was killed by a signal 
    else if (WIFSIGNALED(status)){
        int sig_num=WTERMSIG(status);

        len = snprintf(buffer,MAX_STATUS_SIZE, "enseash [sign:%d|%ldms] %% ", sig_num, period_ms);
    }
    

    write(STDOUT_FILENO , buffer , len);
}
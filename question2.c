#define _POSIX_C_SOURCE 199309L
#include "question1.h"
#include "question2.h"
#include "question4.h"
#include "question6.h"
#include <time.h>



void execute_one_simple_command(char *buffer){
    int status;
    pid_t pid;
    ssize_t bytes_read;

    struct timespec start, end;
    long elapsed_ms = 0;

    // to check if it's the first time to enter the loop

    int first_return = 1 ;

    char *argv[MAX_ARGS];


    while (1) {

        if(first_return){
            show_prompt();
            first_return = 0 ;
        }
        else{
            show_status_prompt(status , elapsed_ms);
        }

        

        //Read the input user
        bytes_read = read(STDIN_FILENO, buffer, MAX_CMD_SIZE);

        // GESTION CTRL+D
        if (bytes_read == 0) {
            write(STDOUT_FILENO, BYE_MSG, strlen(BYE_MSG));
            break; 
        }

        // the -1 
        buffer[bytes_read - 1] = '\0';

        //if the user typed exit 
        if (strcmp(buffer, "exit") == 0) {
            write(STDOUT_FILENO, BYE_MSG, strlen(BYE_MSG));
            break;
        }

        // the function that cuts the complex command 
        parse_arguments(buffer, argv);

        //Start the clock
        clock_gettime(CLOCK_REALTIME , &start);

        // The pqrt of the code that excutes the commande
        pid = fork();

        if (pid == -1) {
            // if the forks fail
            write(STDOUT_FILENO, ERROR_FORK, strlen(ERROR_FORK));
            exit(EXIT_FAILURE);
        }


        if (pid == 0) {

            execvp(argv[0], argv);

            char *error_msg = "Command not found\n";
            write(STDOUT_FILENO, error_msg, strlen(error_msg));
            exit(EXIT_FAILURE);
        }

         else {
            wait(&status);
            //Stop the clock 
            clock_gettime(CLOCK_REALTIME , &end);
            //Calculate the period
            elapsed_ms = (end.tv_sec - start.tv_sec) * 1000 +  (end.tv_nsec - start.tv_nsec) / 1000000;
        }
    }
}
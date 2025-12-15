#include "question1.h"
#include "question2.h"
#include "question4.h"


void execute_one_simple_command(char *buffer){
    int status;
    pid_t pid;
    ssize_t bytes_read;

    // to check if it's the first time to enter the loop

    int first_return = 1 ;


    while (1) {

        if(first_return){
            show_prompt();
            first_return = 0 ;
        }
        else{
            show_status_prompt(status);
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

        // The pqrt of the code that excutes the commande
        pid = fork();

        if (pid == -1) {
            // if the forks fail
            write(STDOUT_FILENO, ERROR_FORK, strlen(ERROR_FORK));
            exit(EXIT_FAILURE);
        }


        if (pid == 0) {

            execlp(buffer, buffer, (char *)NULL);

            char *error_msg = "Command not found\n";
            write(STDOUT_FILENO, error_msg, strlen(error_msg));
            exit(EXIT_FAILURE);
        }

         else {
            wait(&status);
        }
    }
}
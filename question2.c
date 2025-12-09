#include "question1.h"
#include "question2.h"


void execute_one_simple_command(char *buffer){
    int status;
    pid_t pid;
    ssize_t bytes_read;
    while (1) {

        show_prompt();

        //Read the input user
        bytes_read = read(STDIN_FILENO, buffer, MAX_CMD_SIZE);

        // the -1 
        buffer[bytes_read - 1] = '\0';

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
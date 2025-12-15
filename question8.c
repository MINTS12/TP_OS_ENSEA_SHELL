#include "question8.h"
#include "question6.h"

int execute_pipe_command(char *buffer){
    // we search for the pipe symbol
    char *pipe_pose = strchr(buffer , '|');

    if (pipe_pose == NULL){
        return -1;
    }

    *pipe_pose= '\0' ;// replace the pipe by the null terminator
    char *cmd1 = buffer ;
    char *cmd2 = pipe_pose + 1 ;

    //create the pipe
    int pipefd[2];
    pipe(pipefd);

    pid_t pid1, pid2;
    int status;

    // the first child which is the first commande that writes
    if ((pid1 = fork())== 0){

        //redirect the standard output to the pipe write we created 
        dup2(pipefd[1],STDOUT_FILENO);

        close(pipefd[0]);
        close(pipefd[1]); // close the pipe after using it 

        char *argv[MAX_ARGS];
        parse_arguments(cmd1, argv);
        execvp(argv[0], argv);


    }

    //the  second child which is the second commande that reads 
       if ((pid2 = fork())== 0){

        //redirect the standard input to read fro,  the pipe read we created 
        dup2(pipefd[0],STDIN_FILENO);

        close(pipefd[1]);
        close(pipefd[0]); // close the pipe after using it 

        char *argv[MAX_ARGS];
        parse_arguments(cmd2, argv);
        execvp(argv[0], argv);


    }
    //close the pipe
    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, NULL, 0); // wait for the first commande we don't need its status of it cuz the status of the whole command is of the second one
    waitpid(pid2, &status, 0);

    //if the second commande status is exit 
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    return 0;

}
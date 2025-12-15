#include "question7.h"


void manage_redirections(char **argv){
    int i = 0;
    while (argv[i] != NULL){

        // redirect the output (>)

        if (strcmp(argv[i] , ">")== 0){
            char *filename = argv[i+1]; // the nez file is the next word

            if (filename == NULL){
                fprintf(stderr, "Error : No such file exist for > \n");
                exit(EXIT_FAILURE);
            }

            int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            
            if (fd == -1){
                perror("open output");
                exit(EXIT_FAILURE);
            }

            dup2(fd , STDOUT_FILENO);//redirect stdout to file 
            close(fd);

            argv[i]=NULL;

        }

        // Input redirection (<)
        else if (strcmp(argv[i] , "<")== 0){
            char *filename = argv[i+1];

            if (filename == NULL){
                fprintf(stderr, "Error : No such file exist for > \n");
                exit(EXIT_FAILURE);
            }

            int fd = open(filename , O_RDONLY);

            if (fd == -1) {
                perror("open input");
                exit(EXIT_FAILURE);
            }

            dup2(fd, STDIN_FILENO); // REDIRECT STDIN TO FILE 
            close(fd);

            argv[i]=NULL;

        }

        i++;
    }
}

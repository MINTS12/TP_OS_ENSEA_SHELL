# TP_OS_ENSEA_SHELL
This project consists of creating a basic shell. The goal is to understand process management , system calls , time management , redirections  and pipes in a Unix environment  , and to write a clean code with meanigful comments no magic numbers , factorize , insightfull names  , and as less printf as possible

## Question 1 : Displaying a Welcome Message

For this we used the function 
```
write(int fd, const void *buf, size_t count);
```
fd : is the file descriptor which is for our case since it's the terminale it's STDOUT_FILENO

## Question 2 : Execution of Simple Commands

**fork()** creates a child process. In the child, **execlp** replaces the current process image with the new program. The parent stays in a loop to keep the shell running.

```for revision for exam 
int execlp(const char *file, const char *arg, ... /*, (char *) NULL */);
```
-file: Name of the executable
-arg: Argument list for the new program
- Must be terminated with (char *) NULL
  
### The problem we faced 
When reading the command using read() , the string includes the \n  character from when the user presses Enter. Passing ls\n to execlp causes the command to fail because the system looks for a file literally named "ls\n".

### The solution we found 

```
buffer[bytes_read - 1] = '\0';
```

## Question 3: Handling the "exit" Command and Ctrl+D

We read the user input. If **read()** returns 0, it means an EOF (Ctrl+D) was detected. If the buffer matches "exit", we break the main loop to close the shell.

## Question 4: Displaying the Return Code/Signal in the Prompt

The parent process uses wait to block until the child finishes. We then analyze the status integer using:

WIFEXITED(status): True if the child terminated normally.

WEXITSTATUS(status): Returns the actual exit code.

WIFSIGNALED(status): True if the child was killed by a signal.

WTERMSIG(status): Returns the signal number.

## Question 5: Execution Time Measurement

We use **CLOCK_MONOTONIC** to measure actual elapsed time.

We capture tp_start before fork() and tp_end after wait(). The duration is calculated as:
```
 elapsed_ms = (end.tv_sec - start.tv_sec) * 1000 +  (end.tv_nsec - start.tv_nsec) / 1000000;

```
## Question 6: Long Commands

What we do is we cut the long command into simple ones using **strtok** that  replaces spaces with \0 and returns pointers to each word. We store these in an array char *args[]. The array must end with NULL so execvp knows when to stop reading arguments.

## Question 7: Input/Output Redirection
If > is detected, we open the file. In the child process, we use dup2(fd, STDOUT_FILENO). This copies the file descriptor into the standard output slot, so the executed command writes to the file instead of the screen.

```for exam revision
open(const char *pathname, int flags, mode_t mode)

dup2(int oldfd, int newfd)
```

## Question 8: Implementation of Pipes

The shell calls **pipe()** before forking.

Child 1: Uses dup2(pipefd[1], STDOUT_FILENO) and executes the first command.

Child 2: Uses dup2(pipefd[0], STDIN_FILENO) and executes the second command.

### Problem faced 

During my first attempt, the second command (e.g., wc) would never finish

### The solution we found 

I learned that the read end of a pipe stays open as long as there is at least one write descriptor open. I had to ensure that both the parent and the first child closed the unused pipe ends immediately after the fork and dup2 calls

## What I learned from this prject 

The coolest thing I learned is how a computer actually starts and manages a program. Before this lab, the terminal felt like a black box. I understand that it’s all about the "Fork-Exec-Wait" cycle.  

I also learned that you have to be very careful with system plumbing.When I was working on pipes and redirections, I realized that if you forget to close even one small file connection, the whole shell can just freeze up. 

It taught me how to think step by step how things works at the low level where the data goes .

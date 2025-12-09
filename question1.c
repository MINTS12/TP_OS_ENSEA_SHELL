#include "question1.h"

// only welco,es the user
void show_welcome_message(void) {
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
}

// Shows the prompt (I separated them cuz this one gonna be used in a loop)
void show_prompt(void) {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}
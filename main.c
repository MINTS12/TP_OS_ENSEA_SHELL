#include "question1.h"
#include "question2.h"

int main(void) {

    char buffer[MAX_CMD_SIZE];

    show_welcome_message();

    execute_one_simple_command(buffer);

    return 0;
 }  
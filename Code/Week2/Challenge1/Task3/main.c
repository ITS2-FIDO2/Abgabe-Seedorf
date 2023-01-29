#include <stdio.h>
#include <string.h>

#include "shell.h"
#include "thread.h"

char rcv_thread_stack[THREAD_STACKSIZE_MAIN];

void *thread_handler(void *arg)
{
    (void) arg;
    puts("I'm in \"thread\" now");
    return NULL;
}

int main(void)
{
    puts("This is Task-03");

    thread_create(rcv_thread_stack, sizeof(rcv_thread_stack),
                  THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST,
                  thread_handler, NULL, "Test thread");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}

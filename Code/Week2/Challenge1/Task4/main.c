/*
 * Copyright (C) 2008, 2009, 2010 Kaspar Schleiser <kaspar@schleiser.de>
 * Copyright (C) 2013 INRIA
 * Copyright (C) 2013 Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */


#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "shell.h"

// include für System Time (im Makefile muss "USEMODULE += xtimer" hinzugefügt werden)
#include "xtimer.h"

#ifdef MODULE_NETIF
#include "net/gnrc/pktdump.h"
#include "net/gnrc.h"
#endif


char stack[THREAD_STACKSIZE_MAIN];


// Überbleibsel von Task 03
void *thread_handler(void *arg)
{
    
    (void) arg;
    puts("I'm in \"thread\" now");
    return NULL;
}


// System time Ausgabe alle 2 Sekunden in microsekunden
void *system_time(void *arg)
{
    int time = 0;
    while(true){
        time = xtimer_now_usec();
        printf("%d \n",time);
        xtimer_sleep(2);
    }

    (void)arg;
    return NULL;
}

static int whats_up(int argc, char **argv) {
    (void)argc;
    (void)argv;

    printf("The roof!\n");
    return 0;
}

const shell_command_t shell_commands[] = {
    {"whats_up", "prints the roof", whats_up},
    { NULL, NULL, NULL}
};

int main(void)
{
#ifdef MODULE_NETIF
    gnrc_netreg_entry_t dump = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL,
                                                          gnrc_pktdump_pid);
    gnrc_netreg_register(GNRC_NETTYPE_UNDEF, &dump);
#endif


puts("This is Task-04");

    // Thread Creation vom Task03
    thread_create(stack, sizeof(stack),
                  THREAD_PRIORITY_MAIN - 1,
                  THREAD_CREATE_STACKTEST,
                  thread_handler, NULL,
                  "thread");

    //Task04 Thread Creation für die System Time 
    thread_create(stack, sizeof(stack),
                  THREAD_PRIORITY_MAIN - 1,
                  THREAD_CREATE_STACKTEST,
                  system_time, NULL,
                  "time");

    char line_buf[SHELL_DEFAULT_BUFSIZE];

    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}

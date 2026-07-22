#include <stdio.h>
#include <stdlib.h>
#include <sys/reboot.h>
#include "get_sudo_access.h"
#include "suspend_system.h"

FILE* run_cmd(const char *cmd)
{
    FILE *output = popen(cmd, "r");
    if (output == NULL) 
    {
        perror("program failed to run");
        exit(EXIT_FAILURE);
    }

    return output;
}

void shutdown_system()
{
    const int result = reboot(RB_POWER_OFF);
    if (result == -1) 
    {
        perror("failed to shutdown");
        exit(EXIT_FAILURE);
    }
}

void reboot_system()
{
    const int result = reboot(RB_AUTOBOOT);
    if (result == -1) 
    {
        perror("failed to reboot");
        exit(EXIT_FAILURE);
    }
}

void hibernate_system()
{
    const int result = reboot(RB_SW_SUSPEND);
    if (result == -1) 
    {
        perror("failed to hibernate");
        exit(EXIT_FAILURE);
    }
}

void log_out()
{
    FILE *output = popen("mmsg dispatch quit", "r");

    if (output == NULL) 
    {
        perror("program failed to run");
        exit(EXIT_FAILURE);
    }
}

int main()
{
    const char *cmd = "echo '1 shutdown\n2 reboot\n3 hibernate\n4 suspend\n5 log out' | rofi -dmenu";
    FILE *output = run_cmd(cmd);

    const char option = fgetc(output);

    if (!req_sudo_access()) 
    {
        fprintf(stderr, "Action is not authorized");
        exit(EXIT_FAILURE);    
    }

    switch (option) 
    {
        case '1': shutdown_system()     ;   break;
        case '2': reboot_system()       ;   break;
        case '3': hibernate_system()    ;   break;
        case '4': suspend_system()      ;   break;
        case '5': log_out()             ;   break;
    }

    return 0;
}
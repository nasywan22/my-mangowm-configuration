#include <stdio.h>
#include <stdlib.h>
#include <sys/reboot.h>
#include <systemd/sd-bus-protocol.h>
#include <systemd/sd-bus.h>
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

void shutdown_system() {
    sd_bus *bus = NULL;
    sd_bus_error error = SD_BUS_ERROR_NULL;

    if (sd_bus_open_system(&bus) < 0) {
        fprintf(stderr, "Failed to connect to system bus\n");
        exit(EXIT_FAILURE);
    }

    if (sd_bus_call_method(bus,
                           "org.freedesktop.login1",
                           "/org/freedesktop/login1",
                           "org.freedesktop.login1.Manager",
                           "PowerOff",        // metode untuk shutdown
                           &error,
                           NULL,
                           "b",               // argumen: interactive (boolean)
                           1) < 0) {
        fprintf(stderr, "Failed to shutdown: %s\n", error.message);
        sd_bus_error_free(&error);
        sd_bus_unref(bus);
        exit(EXIT_FAILURE);
    }

    sd_bus_unref(bus);
}

void reboot_system() {
    sd_bus *bus = NULL;
    sd_bus_error error = SD_BUS_ERROR_NULL;

    if (sd_bus_open_system(&bus) < 0) {
        fprintf(stderr, "Failed to connect to system bus\n");
        exit(EXIT_FAILURE);
    }

    if (sd_bus_call_method(bus,
                           "org.freedesktop.login1",
                           "/org/freedesktop/login1",
                           "org.freedesktop.login1.Manager",
                           "Reboot",          // metode untuk reboot
                           &error,
                           NULL,
                           "b",
                           1) < 0) {
        fprintf(stderr, "Failed to reboot: %s\n", error.message);
        sd_bus_error_free(&error);
        sd_bus_unref(bus);
        exit(EXIT_FAILURE);
    }

    sd_bus_unref(bus);
}

void hibernate_system() {
    sd_bus *bus = NULL;
    sd_bus_error error = SD_BUS_ERROR_NULL;

    if (sd_bus_open_system(&bus) < 0) {
        fprintf(stderr, "Failed to connect to system bus\n");
        exit(EXIT_FAILURE);
    }

    if (sd_bus_call_method(bus,
                           "org.freedesktop.login1",
                           "/org/freedesktop/login1",
                           "org.freedesktop.login1.Manager",
                           "Hibernate",       // metode untuk hibernate
                           &error,
                           NULL,
                           "b",
                           1) < 0) {
        fprintf(stderr, "Failed to hibernate: %s\n", error.message);
        sd_bus_error_free(&error);
        sd_bus_unref(bus);
        exit(EXIT_FAILURE);
    }

    sd_bus_unref(bus);
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

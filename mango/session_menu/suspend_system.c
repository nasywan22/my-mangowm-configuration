#include <stdio.h>
#include <stdlib.h>
#include <systemd/sd-bus-protocol.h>
#include <systemd/sd-bus.h>

void suspend_system()
{
    sd_bus *bus = NULL;
    sd_bus_error error = SD_BUS_ERROR_NULL;

    if (sd_bus_open_system(&bus) < 0)
    {
        fprintf(stderr, "Failed to connect to dbus");
        exit(EXIT_FAILURE);
    }

    if (sd_bus_call_method(
        bus, 
        "org.freedesktop.login1", 
        "/org/freedesktop/login1", 
        "org.freedesktop.login1.Manager", 
        "Suspend", 
        &error, 
        NULL, 
        "b", 
        1
    ) < 0) 
    {
        fprintf(stderr, "Fialed to execute suspend: %s\n", error.message);
        sd_bus_error_free(&error);
        sd_bus_unref(bus);
    }

    sd_bus_unref(bus);
}
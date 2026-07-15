#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE* run_cmd (char *cmd)
{
    FILE *cmd_o = popen(cmd, "r");

    if (cmd_o == NULL) 
    {
        perror("failed to run program");
        exit(EXIT_FAILURE);
    }

    return cmd_o;
}

int main ()
{
    char *cmd = (char[100]) { "/home/gallahard/.config/mango/window_focus_switcher/get_all_windows | rofi -dmenu -p 'find window'" };
    FILE *cmd_o = run_cmd(cmd);
    char window_id[10];
    fscanf(cmd_o, "%5s", window_id);

    strncpy(cmd, "mmsg dispatch focusid client,", 31);
    strncat(cmd, window_id, 5);

    pclose(cmd_o);
    cmd_o = run_cmd(cmd);
    pclose(cmd_o);

    return EXIT_SUCCESS;
}
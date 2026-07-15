#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool read_line(char buffer[], unsigned int buffer_size, FILE *cmd_o_p)
{
    return fgets(buffer, buffer_size, cmd_o_p);
}

void realloc_m (unsigned int curr_m_size, char *buffer, char *all_win_obj) 
{
    curr_m_size += strlen(buffer);
    char *m_tmp = realloc(all_win_obj, curr_m_size);

    if (m_tmp == NULL) 
    {
        printf("Failed to reallocate memory");
        free(all_win_obj);
        exit(EXIT_FAILURE);
    }

    all_win_obj = m_tmp;
}

FILE* run_cmd (char *all_win_obj)
{
    const char *get_all_windows_cmd = "mmsg get all-clients | jq -crj '[.clients[] | {window_id: .id, appid: .appid, window_title: .title}]'";

    FILE *cmd_o_p = popen(get_all_windows_cmd, "r");

    if (cmd_o_p == NULL)
    {
        printf("Failed to run command");
        free(all_win_obj);
        exit(EXIT_SUCCESS);
    }

    return cmd_o_p;
}

void store_output 
(
    char *buffer,
    unsigned int curr_m_size, 
    FILE *cmd_o_p, 
    char *all_win_obj
)
{
    while (read_line(buffer, curr_m_size, cmd_o_p)) 
    {
       if (strlen(all_win_obj) == curr_m_size) 
       {
            realloc_m(curr_m_size, buffer, all_win_obj);
       } 
       strcat(all_win_obj, buffer);
    }
}

cJSON* parse_obj_to_json (char *all_win_obj)
{
    cJSON *all_win_json = cJSON_Parse(all_win_obj);

    if (all_win_json == NULL) 
    {
        const char *error = cJSON_GetErrorPtr();
        fprintf(stderr, "Parse error: %s\n", error);
        exit(EXIT_FAILURE);
    }

    return all_win_json;
}

void print_all_windows (cJSON *all_win_json)
{
    cJSON *window = NULL;
    cJSON_ArrayForEach(window, all_win_json) {
        cJSON *info = NULL;
        cJSON_ArrayForEach(info, window) {
            if (strcmp(info->string, "appid") == 0) 
            {
                printf("%s - ", info->valuestring);
            } else if (strcmp(info->string, "window_title") == 0) 
            {
                printf("( %s )", info->valuestring);
            } else if (strcmp(info->string, "window_id") == 0) {
                printf("%d | ", info->valueint);
            }
        }
        printf("\n");
    }
}

int main()
{
    // reserve container/memory
    unsigned int curr_m_size = 1 * 1024;
    char *all_win_obj = malloc(curr_m_size);
    char buffer[curr_m_size];

    // run commmand to get all available opened windows
    FILE *cmd_o_p = run_cmd(all_win_obj);

    // store command output to all_win_obj container/memory
    store_output(buffer, curr_m_size, cmd_o_p, all_win_obj);

    // pclose after using it
    pclose(cmd_o_p);

    // Parse obj string to json
    cJSON *all_win_json = parse_obj_to_json(all_win_obj);

    // Print list of all windows
    print_all_windows(all_win_json);

    return EXIT_SUCCESS;
}
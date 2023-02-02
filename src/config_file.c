#include "../include/config_file.h"

void read_config_file() {
    FILE *file_ptr;
    char line[1024];

    file_ptr = fopen("byolb.config", "r");

    if (file_ptr == NULL) {
        logger("Failed to open the byolb.config file");
        return;
    }

    struct target_group curr_target_group;
    while (fgets(line, sizeof(line), file_ptr) != NULL) {
        char *trimmed_line = trim(line);

        // tg {
        if (str_starts_with(trimmed_line, "tg") &&
            str_ends_with(trimmed_line, "{")) {
            // initalize tg
            curr_target_group.is_default = 0;
            curr_target_group.priority = 0;
            curr_target_group.round_robin_current = NULL;
            curr_target_group.round_robin_head = NULL;
            curr_target_group.round_robin_mutex =
                (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
        }

        // path
        else if (str_starts_with(trimmed_line, "path")) {
            char *key = strtok(trimmed_line, " ");
            char *value = strtok(NULL, " ");
            strcpy(curr_target_group.path, value);
        }

        // priority
        else if (str_starts_with(trimmed_line, "priority")) {
            char *key = strtok(trimmed_line, " ");
            char *value = strtok(NULL, " ");
            int value_int = atoi(value);
            curr_target_group.priority = value_int;
        }

        // default
        else if (str_starts_with(trimmed_line, "default")) {
            curr_target_group.is_default = 1;
        }

        // target
        else if (str_starts_with(trimmed_line, "target")) {
            char *key = strtok(trimmed_line, " ");
            char *serverName = strtok(NULL, " ");
            char *host = strtok(NULL, " ");
            char *port_str = strtok(NULL, " ");
            int port = atoi(port_str);

            struct target_backend server;
            strcpy(server.name, serverName);
            strcpy(server.host, host);
            server.port = port;
            server.is_healthy = 1;
            insert_to_round_robin(&curr_target_group.round_robin_head, server);
        }

        // }
        else if (str_starts_with(trimmed_line, "}")) {
            target_group_list_sorted_insert(curr_target_group);
        }
    }

    // Close the file
    fclose(file_ptr);
}
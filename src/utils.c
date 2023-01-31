#include "../include/utils.h"

char *parse_status_code(char *response) {
    const char *seperator = " ";
    char *token = strtok(response, seperator);
    token = strtok(NULL, seperator);

    return token;
}

char *parse_url(char *request) {
    const char *seperator = " ";
    char *token = strtok(request, seperator);
    token = strtok(NULL, seperator);

    return token;
}

void add_status_code_to_response(char *response, char *status_code,
                                 char *http_version) {
    strcat(response, http_version);
    strcat(response, " ");
    strcat(response, status_code);
    strcat(response, "\n");
}

void add_header_to_response(char *response, char *header_name,
                            char *header_value) {
    strcat(response, header_name);
    strcat(response, ": ");
    strcat(response, header_value);
    strcat(response, "\n");
}

void add_content_to_response(char *response, char *content) {
    strcat(response, "\n");
    strcat(response, content);
}
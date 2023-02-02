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

char *ltrim(char *s) {
    while (isspace(*s)) s++;
    return s;
}

char *rtrim(char *s) {
    char *back = s + strlen(s);
    while (isspace(*--back))
        ;
    *(back + 1) = '\0';
    return s;
}

char *trim(char *s) { return rtrim(ltrim(s)); }

int str_starts_with(const char *a, const char *b) {
    if (strncmp(a, b, strlen(b)) == 0) return 1;
    return 0;
}

int str_ends_with(const char *a, const char *b) {
    const char *test_on = a + strlen(a) - strlen(b);
    if (strcmp(test_on, b) == 0) return 1;
    return 0;
}
#include "../include/utils.h"

/**
 * @brief parse the HTTP status code from the response
 *
 * @param response
 * @return char*
 */
char *parse_status_code(char *response) {
    const char *seperator = " ";
    char *token = strtok(response, seperator);
    token = strtok(NULL, seperator);

    return token;
}

/**
 * @brief parse the url from the request
 *
 * @param request
 * @return char*
 */
char *parse_url(char *request) {
    const char *seperator = " ";
    char *token = strtok(request, seperator);
    token = strtok(NULL, seperator);

    return token;
}

/**
 * @brief add status code in the response string
 *
 * @param response
 * @param status_code
 * @param http_version
 */
void add_status_code_to_response(char *response, char *status_code,
                                 char *http_version) {
    strcat(response, http_version);
    strcat(response, " ");
    strcat(response, status_code);
    strcat(response, "\n");
}

/**
 * @brief add a header to the response string
 *
 * @param response
 * @param header_name
 * @param header_value
 */
void add_header_to_response(char *response, char *header_name,
                            char *header_value) {
    strcat(response, header_name);
    strcat(response, ": ");
    strcat(response, header_value);
    strcat(response, "\n");
}

/**
 * @brief add the content to the response
 *
 * @param response
 * @param content
 */
void add_content_to_response(char *response, char *content) {
    strcat(response, "\n");
    strcat(response, content);
}

/**
 * @brief left trim space
 *
 * @param s
 * @return char*
 */
char *ltrim(char *s) {
    while (isspace(*s)) s++;
    return s;
}

/**
 * @brief right trim space
 *
 * @param s
 * @return char*
 */
char *rtrim(char *s) {
    char *back = s + strlen(s);
    while (isspace(*--back))
        ;
    *(back + 1) = '\0';
    return s;
}

/**
 * @brief trim both left and right spaces
 *
 * @param s
 * @return char*
 */
char *trim(char *s) { return rtrim(ltrim(s)); }

/**
 * @brief check if a string a starts with b
 *
 * @param a
 * @param b
 * @return int
 */
int str_starts_with(const char *a, const char *b) {
    if (strncmp(a, b, strlen(b)) == 0) return 1;
    return 0;
}

/**
 * @brief check if a string a ends with b
 *
 * @param a
 * @param b
 * @return int
 */
int str_ends_with(const char *a, const char *b) {
    const char *test_on = a + strlen(a) - strlen(b);
    if (strcmp(test_on, b) == 0) return 1;
    return 0;
}
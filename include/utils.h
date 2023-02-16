#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *parse_status_code(char *response);
char *parse_url(char *request);

void add_status_code_to_response(char *response, char *status_code,
                                 char *http_version);

void add_header_to_response(char *response, char *header_name,
                            char *header_value);

void add_content_to_response(char *response, char *content);

char *ltrim(char *s);

char *rtrim(char *s);

char *trim(char *s);

int str_starts_with(const char *a, const char *b);

int str_ends_with(const char *a, const char *b);

#endif  // UTILS_H
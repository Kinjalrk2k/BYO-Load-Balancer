#ifndef ENV_H
#define ENV_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setup_env();
unsigned int get_env_port();
unsigned int get_env_backlog();
char *get_env_host();

#endif  // ENV_H
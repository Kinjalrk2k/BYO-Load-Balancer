#ifndef LOGGING_H
#define LOGGING_H

#include <stdarg.h>
#include <stdio.h>

#include "./env.h"

int logger(char *format, ...);
void log_err(char *format, ...);

#endif  // LOGGING_H
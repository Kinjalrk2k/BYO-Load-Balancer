#include "../include/logging.h"

/**
 * @brief log data into the console
 *
 * @param format
 * @param ...
 * @return int
 */
int logger(char *format, ...) {
    va_list args;
    va_start(args, format);

    int response = vprintf(format, args);
    printf("\n");

    va_end(args);
    return response;
}
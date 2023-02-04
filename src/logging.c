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

void log_err(char *format, ...) {
    va_list args;
    va_start(args, format);
    if (get_env_log_errors() == 1) {
        char err_str[1000];
        vsnprintf(err_str, 1000, format, args);

        char err_str_label[1000];
        sprintf(err_str_label, "[ERROR] %s", err_str);
        perror(err_str_label);
    }
    va_end(args);
}

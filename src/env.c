#include "../include/env.h"

unsigned int port;
unsigned int backlog;
char *host;
unsigned int log_errors;

void setup_env() {
    host = getenv("HOST");
    if (host == NULL) {
        host = (char *)(malloc(30));
        strcpy(host, "localhost");
    }

    char *port_str = getenv("PORT");
    if (port_str == NULL) {
        port_str = (char *)(malloc(8));
        strcpy(port_str, "2209");
    }
    port = atoi(port_str);

    char *backlog_str = getenv("BACKLOG");
    if (backlog_str == NULL) {
        backlog_str = (char *)(malloc(8));
        strcpy(backlog_str, "10");
    }
    backlog = atoi(backlog_str);

    char *log_errors_str = getenv("LOG_ERRORS");
    if (log_errors_str == NULL) {
        log_errors_str = (char *)(malloc(2));
        strcpy(log_errors_str, "0");
    }
    log_errors = atoi(log_errors_str);
}

unsigned int get_env_port() { return port; }

unsigned int get_env_backlog() { return backlog; }

char *get_env_host() { return host; }

unsigned int get_env_log_errors() { return log_errors; }
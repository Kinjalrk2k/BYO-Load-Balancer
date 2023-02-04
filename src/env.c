#include "../include/env.h"

unsigned int port;
unsigned int backlog;
char *host;

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
}

unsigned int get_env_port() { return port; }

unsigned int get_env_backlog() { return backlog; }

char *get_env_host() { return host; }

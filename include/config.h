#ifndef CONFIG_H
#define CONFIG_H

#include <arpa/inet.h>

struct target_backend {
    char host[INET6_ADDRSTRLEN];
    unsigned int port;
    int is_healthy;  // 0 - unhealthy , 1 - healthy
};

#endif  // CONFIG_H
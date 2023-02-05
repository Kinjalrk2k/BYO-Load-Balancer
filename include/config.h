#ifndef CONFIG_H
#define CONFIG_H

#include <arpa/inet.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "./env.h"

struct target_backend {
    char name[100];
    char host[INET6_ADDRSTRLEN];
    unsigned int port;
    int is_healthy;  // 0 - unhealthy , 1 - healthy
};

struct round_robin_node {
    struct target_backend backend;
    struct round_robin_node *next;
};

struct target_group {
    char path[100];
    int priority;
    struct round_robin_node *round_robin_head;
    struct round_robin_node *round_robin_current;
    int is_default;
    pthread_mutex_t round_robin_mutex;
};

#endif  // CONFIG_H
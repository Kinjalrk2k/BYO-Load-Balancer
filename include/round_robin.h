#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "./config.h"
#include "./health_check.h"

#define HEALTH_CHECK_INTERVAL 30  // in seconds

struct round_robin_node {
    struct target_backend backend;
    struct round_robin_node *next;
};

void insert_to_round_robin(struct target_backend backend);
struct target_backend get_next_backend();
void health_check_all_targets();
void build_passive_health_check_thread();

#endif  // ROUND_ROBIN_H
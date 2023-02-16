#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "./config.h"
#include "./health_check.h"

void insert_to_round_robin(struct round_robin_node **round_robin_head,
                           struct target_backend backend);

struct target_backend get_next_backend(
    struct round_robin_node *round_robin_head,
    struct round_robin_node **round_robin_current, pthread_mutex_t mutex);

void health_check_all_targets(struct round_robin_node **round_robin_head,
                              pthread_mutex_t mutex);

#endif  // ROUND_ROBIN_H
#ifndef TARGET_GROUP_H
#define TARGET_GROUP_H

#include <pthread.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#include "./round_robin.h"

struct target_group {
    char path[100];
    int priority;
    struct round_robin_node *round_robin_head;
    struct round_robin_node *round_robin_current;
    int is_default;
    pthread_mutex_t round_robin_mutex;
};

struct target_group_list_node {
    struct target_group tg;
    struct target_group_list_node *next;
};

void target_group_list_sorted_insert(struct target_group target_group);
void find_target_group_with_path(char *path, struct target_group **tg);
void health_check_all_target_groups();

#endif  // TARGET_GROUP_H
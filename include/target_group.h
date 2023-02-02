#ifndef TARGET_GROUP_H
#define TARGET_GROUP_H

#include <pthread.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#include "./round_robin.h"

#define HEALTH_CHECK_INTERVAL 30  // in seconds

struct target_group_list_node {
    struct target_group tg;
    struct target_group_list_node *next;
};

void target_group_list_sorted_insert(struct target_group target_group);
void find_target_group_with_path(char *path, struct target_group **tg);
void health_check_all_target_groups();

void *passive_health_check(void *arg);
void build_passive_health_check_thread();

void get_health_json(char *json);

#endif  // TARGET_GROUP_H
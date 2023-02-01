#ifndef TARGET_GROUP_H
#define TARGET_GROUP_H

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
};

struct target_group_list_node {
    struct target_group tg;
    struct target_group_list_node *next;
};

void target_group_list_sorted_insert(struct target_group target_group);
struct target_group find_target_group_with_path(char *path);

#endif  // TARGET_GROUP_H
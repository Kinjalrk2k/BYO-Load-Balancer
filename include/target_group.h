#ifndef TARGET_GROUP_H
#define TARGET_GROUP_H

#include "./round_robin.h"

struct target_group {
    char path[100];
    int priority;
    struct round_robin_node *round_robin_head;
    struct round_robin_node *round_robin_current;
};

#endif  // TARGET_GROUP_H
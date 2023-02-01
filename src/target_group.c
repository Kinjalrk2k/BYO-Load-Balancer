#include "../include/target_group.h"

struct target_group_list_node *target_groups_head = NULL;

pthread_mutex_t target_group_mutex = PTHREAD_MUTEX_INITIALIZER;

void target_group_list_sorted_insert(struct target_group target_group) {
    struct target_group_list_node *new_target_group_node =
        (struct target_group_list_node *)malloc(
            sizeof(struct target_group_list_node));
    new_target_group_node->tg = target_group;

    struct target_group_list_node *temp;

    if (target_groups_head == NULL ||
        target_groups_head->tg.priority >= target_group.priority) {
        new_target_group_node->next = target_groups_head;
        target_groups_head = new_target_group_node;
    } else {
        temp = target_groups_head;
        while (temp->next != NULL &&
               temp->next->tg.priority < target_group.priority) {
            temp = temp->next;
        }
        new_target_group_node->next = temp->next;
        temp->next = new_target_group_node;
    }
}

void find_target_group_with_path(char *path, struct target_group **tg) {
    // pthread_mutex_lock(&target_group_mutex);

    struct target_group_list_node *temp = target_groups_head;
    struct target_group *default_tg = &target_groups_head->tg;

    regex_t path_regex;
    int regex_result;

    while (temp != NULL) {
        if (temp->tg.is_default == 1) {  // found the default!
            default_tg = &temp->tg;
        }

        regcomp(&path_regex, temp->tg.path, 0);
        regex_result = regexec(&path_regex, path, 0, NULL, 0);
        if (regex_result == 0) {
            // pthread_mutex_unlock(&target_group_mutex);
            *tg = &temp->tg;
            return;
        }

        temp = temp->next;
    }

    // pthread_mutex_unlock(&target_group_mutex);
    *tg = default_tg;
}

void health_check_all_target_groups() {
    logger("Health check started");
    struct target_group_list_node *temp = target_groups_head;

    while (temp != NULL) {
        health_check_all_targets(&temp->tg.round_robin_head);
        temp = temp->next;
    }
    logger("Health check ended");
}
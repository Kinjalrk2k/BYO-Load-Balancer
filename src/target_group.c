#include "../include/target_group.h"

struct target_group_list_node *target_groups_head = NULL;

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

struct target_group find_target_group_with_path(char *path) {
    struct target_group_list_node *temp = target_groups_head;
    struct target_group default_tg = target_groups_head->tg;

    regex_t path_regex;
    int regex_result;

    while (temp != NULL) {
        logger("%s", temp->tg.path);
        if (temp->tg.is_default == 1) {  // found the default!
            default_tg = temp->tg;
        }

        regcomp(&path_regex, temp->tg.path, 0);
        regex_result = regexec(&path_regex, path, 0, NULL, 0);
        if (regex_result == 0) {
            return temp->tg;
        }

        temp = temp->next;
    }

    logger("default");
    return default_tg;
}
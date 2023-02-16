#include "../include/round_robin.h"

/**
 * @brief insert a node to the round robin circular linked list
 *
 * @param round_robin_head
 * @param backend
 */
void insert_to_round_robin(struct round_robin_node **round_robin_head,
                           struct target_backend backend) {
    // struct round_robin_node *round_robin_head = *p_round_robin_head;
    struct round_robin_node *new_node =
        (struct round_robin_node *)malloc(sizeof(struct round_robin_node));

    new_node->backend = backend;

    if (*round_robin_head == NULL) {
        // empty circular linked list
        *round_robin_head = new_node;
        new_node->next = *round_robin_head;
    } else {
        struct round_robin_node *temp = *round_robin_head;
        while (temp->next != *round_robin_head) {
            temp = temp->next;
        }

        temp->next = new_node;
        new_node->next = *round_robin_head;
    }
}

/**
 * @brief Get the next healthy target (node) from the circular linked list
 *
 * @param round_robin_head
 * @param round_robin_current
 * @param mutex
 * @return struct target_backend
 */
struct target_backend get_next_backend(
    struct round_robin_node *round_robin_head,
    struct round_robin_node **round_robin_current, pthread_mutex_t mutex) {
    pthread_mutex_lock(&mutex);
    struct round_robin_node *temp = *round_robin_current;

    if (temp == NULL) {  // first time here, start with the head
        temp = round_robin_head;
        *round_robin_current = round_robin_head;
    } else {
        temp = temp->next;
    }

    // loop back till current
    while (temp->next != *round_robin_current) {
        if (temp->backend.is_healthy == 1) {  // choose only if healthy
            *round_robin_current = temp;
            pthread_mutex_unlock(&mutex);
            return temp->backend;  // got a healthy one!
        }
        temp = temp->next;
    }

    // the last node didn't get a chance to be processed
    if (temp->backend.is_healthy == 1) {  // choose only if healthy
        *round_robin_current = temp;
        pthread_mutex_unlock(&mutex);
        return temp->backend;  // got a healthy one!
    } else {
        temp = temp->next;
    }

    pthread_mutex_unlock(&mutex);
    return temp->backend;
}

/**
 * @brief loop and check health of all the targets in the circular linked list
 *
 * @param round_robin_head
 * @param mutex
 */
void health_check_all_targets(struct round_robin_node **round_robin_head,
                              pthread_mutex_t mutex) {
    pthread_mutex_lock(&mutex);

    struct round_robin_node *temp = *round_robin_head;
    while (temp->next != *round_robin_head) {
        temp->backend.is_healthy = health_check_target(temp->backend);
        temp = temp->next;
    }
    temp->backend.is_healthy = health_check_target(temp->backend);  // last node

    pthread_mutex_unlock(&mutex);
}

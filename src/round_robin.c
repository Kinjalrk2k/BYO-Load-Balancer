#include "../include/round_robin.h"

pthread_mutex_t round_robin_mutex = PTHREAD_MUTEX_INITIALIZER;

void insert_to_round_robin(struct round_robin_node **round_robin_head,
                           struct target_backend backend) {
    // struct round_robin_node *round_robin_head = *p_round_robin_head;
    struct round_robin_node *new_node =
        (struct round_robin_node *)malloc(sizeof(struct round_robin_node));

    new_node->backend = backend;

    if (*round_robin_head == NULL) {
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

struct target_backend get_next_backend(
    struct round_robin_node *round_robin_head,
    struct round_robin_node **round_robin_current) {
    pthread_mutex_lock(&round_robin_mutex);
    struct round_robin_node *temp = *round_robin_current;

    if (temp == NULL) {  // first time here, start with the head
        temp = round_robin_head;
    } else {
        temp = temp->next;
    }

    while (temp->next != *round_robin_current) {
        if (temp->backend.is_healthy == 1) {  // return the next healthy backend
            *round_robin_current = temp;
            pthread_mutex_unlock(&round_robin_mutex);
            return temp->backend;
        }
        temp = temp->next;
    }

    if (temp->backend.is_healthy == 1) {  // return the next healthy backend
        *round_robin_current = temp;
        pthread_mutex_unlock(&round_robin_mutex);
        return temp->backend;
    }

    pthread_mutex_unlock(&round_robin_mutex);
    return temp->backend;
}

void health_check_all_targets(struct round_robin_node **round_robin_head) {
    logger("Health check started");
    pthread_mutex_lock(&round_robin_mutex);

    struct round_robin_node *temp = *round_robin_head;
    while (temp->next != *round_robin_head) {
        temp->backend.is_healthy = health_check_target(temp->backend);
        temp = temp->next;
    }
    temp->backend.is_healthy = health_check_target(temp->backend);

    pthread_mutex_unlock(&round_robin_mutex);
    logger("Health check ended");
}

// void *passive_health_check(void *arg) {
//     while (1) {
//         sleep(HEALTH_CHECK_INTERVAL);
//         health_check_all_targets();
//     }
// }

// void build_passive_health_check_thread() {
//     pthread_t passive_health_check_thread;
//     pthread_create(&passive_health_check_thread, NULL, &passive_health_check,
//                    NULL);
// }

// // TODO: make this better
// void get_health_in_json(struct round_robin_node *round_robin_head, char
// *json) {
//     pthread_mutex_lock(&round_robin_mutex);

//     strcpy(json, "{ \"servers\": [");

//     struct round_robin_node *temp = round_robin_head;
//     while (temp->next != round_robin_head) {
//         strcat(json, "{ \"name\": \"");
//         strcat(json, temp->backend.name);
//         strcat(json, "\", \"status\": \"");
//         strcat(json, temp->backend.is_healthy == 1 ? "up" : "down");
//         strcat(json, "\" }, ");

//         temp = temp->next;
//     }

//     strcat(json, "{ \"name\": \"");
//     strcat(json, temp->backend.name);
//     strcat(json, "\", \"status\": \"");
//     strcat(json, temp->backend.is_healthy == 1 ? "up" : "down");
//     strcat(json, "\" }, ");

//     strcat(json, "\b\b] }");

//     pthread_mutex_unlock(&round_robin_mutex);
// }
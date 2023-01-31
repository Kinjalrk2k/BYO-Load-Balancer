#include "../include/round_robin.h"

struct round_robin_node *round_robin_head = NULL;
struct round_robin_node *round_robin_current = NULL;
int round_robin_size = 0;

pthread_mutex_t round_robin_mutex = PTHREAD_MUTEX_INITIALIZER;

void insert_to_round_robin(struct target_backend backend) {
    struct round_robin_node *new_node =
        (struct round_robin_node *)malloc(sizeof(struct round_robin_node));

    new_node->backend = backend;

    if (round_robin_head == NULL) {
        round_robin_head = new_node;
        round_robin_head->next = round_robin_head;
    } else {
        struct round_robin_node *temp = round_robin_head;
        while (temp->next != round_robin_head) {
            temp = temp->next;
        }

        temp->next = new_node;
        new_node->next = round_robin_head;
    }

    round_robin_size++;
}

struct target_backend get_next_backend() {
    pthread_mutex_lock(&round_robin_mutex);

    struct round_robin_node *temp = round_robin_current;

    if (temp == NULL) {  // first time here, start with the head
        temp = round_robin_head;
    } else {
        temp = temp->next;
    }

    while (temp->next != round_robin_current) {
        if (temp->backend.is_healthy == 1) {  // return the next healthy backend
            round_robin_current = temp;
            pthread_mutex_unlock(&round_robin_mutex);
            return round_robin_current->backend;
        }
        temp = temp->next;
    }

    pthread_mutex_unlock(&round_robin_mutex);
    return round_robin_current->backend;
}
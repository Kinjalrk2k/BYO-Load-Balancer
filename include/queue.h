#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct connection_queue_node {
    int *p_client_socket_fd;
    struct connection_queue_node *next;
};

void enqueue_connection(int *client_socket_fd);
int *dequeue_connection();
int connection_queue_size();

#endif  // QUEUE_H
#ifndef CONNECTION_H
#define CONNECTION_H

#define BUFSIZE 8192

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "./networking.h"
#include "./queue.h"
#include "./round_robin.h"
#include "./server.h"
#include "./target_group.h"
#include "./utils.h"

#define HTTP_STATUS_OK 200

void handle_503(struct socket_connection target_socket, int new_connection);

int handle_routing_target(char *request_buffer, struct target_backend *p_target,
                          int new_connection);

int handle_routing_target(char *request_buffer, struct target_backend *p_target,
                          int new_connection);

void handle_health_route(int new_connection);

void connection_loop(struct socket_connection client_socket);

void *thread_handler(void *arg);

void *handle_connection(void *p_client_socket);

#endif  // CONNECTION_H
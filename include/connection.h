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

void connection_loop(struct socket_connection client_socket);
void *thread_handler(void *arg);
void *handle_connection(void *p_client_socket);

#endif  // CONNECTION_H
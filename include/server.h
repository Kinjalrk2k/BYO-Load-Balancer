#ifndef SERVER_H
#define SERVER_H

#include "./networking.h"

int create_server(struct socket_connection *server_socket, char *host,
                  unsigned int port, unsigned int backlog);

int accept_incoming_connection(struct socket_connection server_socket);

int connect_to_target(struct socket_connection *target_socket, char *host,
                      unsigned int port);

#endif  // SERVER_H
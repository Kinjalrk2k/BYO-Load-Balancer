#ifndef CONNECTION_H
#define CONNECTION_H

#define BUFSIZE 8192

#include "./networking.h"
#include "./server.h"

void connection_loop(struct socket_connection client_socket);

#endif  // CONNECTION_H
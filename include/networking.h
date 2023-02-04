#ifndef NETWORKING_H
#define NETWORKING_H

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "./logging.h"

struct socket_name_info {
    char host[INET6_ADDRSTRLEN];
    char port[NI_MAXSERV];
};

struct socket_connection {
    int socket_fd;
    struct sockaddr_in address;
    struct socket_name_info socket_name;
};

int hostname_to_ip(char *hostname, unsigned int port, char *ip);

int get_socket(struct socket_connection *server_socket, char *address,
               unsigned int port);

int bind_to_socket(struct socket_connection server_socket);
int connect_to_socket(struct socket_connection server_socket);

int listen_to_socket(struct socket_connection server_socket,
                     unsigned int backlog);

#endif  // NETWORKING_H
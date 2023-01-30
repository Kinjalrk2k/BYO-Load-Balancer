#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../include/logging.h"
#include "../include/networking.h"
#include "../include/server.h"

#define BUFSIZE 8192

int main(int argc, char *argv[]) {
    int new_connection, bytes_read;
    char buffer[BUFSIZE];
    struct socket_connection client_socket, target_socket;

    /* Create a listening socket */
    if (create_server(&client_socket, "127.0.0.1", 2209, 10) < 0) {
        perror("Failed to create the server");
        return 1;
    }

    while (1) {
        /* Accept incoming client connections */
        new_connection = accept_incoming_connection(client_socket);
        if (new_connection < 0) continue;

        /* Create a target socket */
        if (connect_to_target(&target_socket, "127.0.0.1", 5000) < 0) continue;

        /* Read the client's request */
        bytes_read = recv(new_connection, buffer, BUFSIZE - 1, 0);

        /* Forward the client's request to the target server */
        send(target_socket.socket_fd, buffer, strlen(buffer), 0);

        /* Read the response from the target and forward it to the client */
        while ((bytes_read =
                    recv(target_socket.socket_fd, buffer, BUFSIZE - 1, 0))) {
            send(new_connection, buffer, bytes_read, 0);
        }

        close(target_socket.socket_fd);
        close(new_connection);
    }

    return 0;
}

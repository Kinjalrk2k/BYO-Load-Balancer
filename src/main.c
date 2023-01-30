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

#define BUFSIZE 8192

int main(int argc, char *argv[]) {
    int new_connection;
    struct sockaddr_in serv_addr;
    char buffer[BUFSIZE];

    struct socket_connection client_socket, target_socket;

    /* Create a listening socket */
    if (get_socket(&client_socket, "127.0.0.1", 2209) < 0) {
        perror("Failed to initialize server socket");
        return 1;
    }

    if (bind_to_socket(client_socket) < 0) {
        perror("Failed to bind server socket");
        return 1;
    }

    if (listen_to_socket(client_socket, 10) < 0) {
        perror("Failed to listen to server socket");
        return 1;
    }

    logger("Server listening on http://%s:%s", client_socket.socket_name.host,
           client_socket.socket_name.port);

    while (1) {
        /* Accept incoming client connections */
        new_connection =
            accept(client_socket.socket_fd, (struct sockaddr *)NULL, NULL);

        if (new_connection == -1) {
            perror("Failed to accept incomming connection");
            continue;
        }

        int n = recv(new_connection, buffer, BUFSIZE - 1, 0);

        /* Create a target socket */
        if (get_socket(&target_socket, "127.0.0.1", 5000) < 0) {
            perror("Failed to initialize target socket");
            close(target_socket.socket_fd);
            close(new_connection);
            continue;
        }

        if (connect_to_socket(target_socket) < 0) {
            perror("Failed to connect to target socket");
            close(target_socket.socket_fd);
            close(new_connection);
            continue;
        }

        /* Forward the client's request to the target server */
        send(target_socket.socket_fd, buffer, strlen(buffer), 0);

        /* Receive the response from the target server and forward it to the
         * client */
        while ((n = recv(target_socket.socket_fd, buffer, BUFSIZE - 1, 0)) >
               0) {
            send(new_connection, buffer, n, 0);
        }

        close(target_socket.socket_fd);
        close(new_connection);
    }

    logger("errno = %d", errno);

    return 0;
}

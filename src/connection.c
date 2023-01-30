#include "../include/connection.h"

void connection_loop(struct socket_connection client_socket) {
    struct socket_connection target_socket;
    int new_connection, bytes_read;
    char buffer[BUFSIZE];

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

        /* close sockets */
        close(target_socket.socket_fd);
        close(new_connection);
    }
}
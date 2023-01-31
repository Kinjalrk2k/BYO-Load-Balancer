#include "../include/connection.h"

void *handle_connection(void *p_new_connection) {
    int new_connection = *((int *)p_new_connection);
    free(p_new_connection);

    struct socket_connection target_socket;
    int bytes_read;
    char buffer[BUFSIZE];

    // get the next target
    struct target_backend target = get_next_backend();

    /* Create a target socket */
    if (connect_to_target(&target_socket, target.host, target.port) < 0) {
        return NULL;
    }

    /* Read the client's request */
    bytes_read = recv(new_connection, buffer, BUFSIZE - 1, 0);

    /* Forward the client's request to the target server */
    send(target_socket.socket_fd, buffer, strlen(buffer), 0);

    /* Read the response from the target and forward it to the client */
    while (
        (bytes_read = recv(target_socket.socket_fd, buffer, BUFSIZE - 1, 0))) {
        send(new_connection, buffer, bytes_read, 0);
    }

    /* close sockets */
    close(target_socket.socket_fd);
    close(new_connection);

    return NULL;
}

void *thread_handler(void *arg) {
    while (1) {  // do not kill the threads
        int *p_new_connection = dequeue_connection();

        if (p_new_connection != NULL) {
            // we've a waiting connection, so handle it!
            handle_connection(p_new_connection);
        }
    }
}

void connection_loop(struct socket_connection client_socket) {
    int new_connection;

    while (1) {
        /* Accept incoming client connections */
        new_connection = accept_incoming_connection(client_socket);
        if (new_connection < 0) continue;

        int *p_new_connection = (int *)malloc(sizeof(int));
        *p_new_connection = new_connection;

        enqueue_connection(p_new_connection);
    }
}
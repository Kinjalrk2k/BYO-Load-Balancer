#include "../include/server.h"

/**
 * @brief Create a server. Create the socket file descriptor, bind an address
 * and then start listening on this socket
 *
 * @param server_socket
 * @param host
 * @param port
 * @param backlog
 * @return int
 */
int create_server(struct socket_connection *server_socket, char *host,
                  unsigned int port, unsigned int backlog) {
    char ip[16];
    if (hostname_to_ip(host, port, ip) < 0) {
        return -4;
    }

    if (get_socket(&(*server_socket), ip, port) < 0) {
        // log_err("Failed to initialize server socket");
        return -1;
    }

    if (bind_to_socket(*server_socket) < 0) {
        // log_err("Failed to bind server socket");
        return -2;
    }

    if (listen_to_socket(*server_socket, backlog) < 0) {
        // log_err("Failed to listen to server socket");
        return -3;
    }

    logger("[INFO] Server listening on http://%s:%s",
           server_socket->socket_name.host, server_socket->socket_name.port);

    return 0;
}

/**
 * @brief accept connections and return the connection file descriptor
 *
 * @param server_socket
 * @return int
 */
int accept_incoming_connection(struct socket_connection server_socket) {
    /**
     * @brief accept an incomming connection
     * @see https://man7.org/linux/man-pages/man2/accept.2.html
     */
    int new_connection_fd =
        accept(server_socket.socket_fd, (struct sockaddr *)NULL, NULL);

    if (new_connection_fd == -1) {
        log_err("Failed to accept incomming connection");
        close(new_connection_fd);
        return -1;
    }

    return new_connection_fd;
}

/**
 * @brief connect to a particular socket
 *
 * @param target_socket
 * @param host
 * @param port
 * @return int
 */
int connect_to_target(struct socket_connection *target_socket, char *host,
                      unsigned int port) {
    if (get_socket(&(*target_socket), host, port) < 0) {
        // log_err("Failed to initialize target socket");
        close(target_socket->socket_fd);
        return -1;
    }

    if (connect_to_socket(*target_socket) < 0) {
        // log_err("Failed to connect to target socket");
        close(target_socket->socket_fd);
        return -2;
    }

    return 0;
}
#include "../include/networking.h"

int hostname_to_ip(char *hostname, unsigned int port, char *ip) {
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_in *h;
    int rv;

    char port_str[7];
    sprintf(port_str, "%d", port);

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // use AF_INET6 to force IPv6
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(hostname, port_str, &hints, &servinfo)) != 0) {
        log_err("Cannot resolve address %s:%d", hostname, port);
        return -1;
    }

    // loop through all the results
    for (p = servinfo; p != NULL; p = p->ai_next) {
        h = (struct sockaddr_in *)p->ai_addr;
        strcpy(ip, inet_ntoa(h->sin_addr));
    }

    freeaddrinfo(servinfo);  // cleanup!

    return 0;
}

int get_socket(struct socket_connection *server_socket, char *address,
               unsigned int port) {
    /**
     * @brief creating the socket endpoint for the server
     * @see https://man7.org/linux/man-pages/man2/socket.2.html
     */
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        log_err("Failed to initiate server socket");
        return -1;
    }

    /**
     * @brief set the server socket options
     * @see https://linux.die.net/man/3/setsockopt
     */
    int option_value = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &option_value,
                   sizeof(option_value)) == -1) {
        log_err("Failed to set server socket options");
        close(socket_fd);
        return -2;
    }

    /**
     * @brief setting and port for building the server address
     * @see https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
     * @see https://linux.die.net/man/3/htonl
     * @see https://man7.org/linux/man-pages/man3/inet_pton.3.html
     * @see https://man7.org/linux/man-pages/man3/memset.3.html
     */
    struct sockaddr_in server_address;
    memset(&server_address, '0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, address, &server_address.sin_addr);
    socklen_t server_address_size = sizeof(server_address);

    /**
     * @brief get the details of the server
     * @see https://man7.org/linux/man-pages/man3/getnameinfo.3.html
     */
    char host_buffer[INET6_ADDRSTRLEN];
    char service_buffer[NI_MAXSERV];
    if (getnameinfo((struct sockaddr *)&server_address, server_address_size,
                    host_buffer, sizeof(host_buffer), service_buffer,
                    sizeof(service_buffer), NI_NUMERICSERV) != 0) {
        log_err("Failed to fetch information about the server");
        return -3;
    }

    server_socket->socket_fd = socket_fd;
    server_socket->address = server_address;
    strcpy(server_socket->socket_name.host, host_buffer);
    strcpy(server_socket->socket_name.port, service_buffer);

    return 0;
}

int bind_to_socket(struct socket_connection server_socket) {
    socklen_t server_address_size = sizeof(server_socket.address);

    /**
     * @brief bind the address of the server to the socket namespace
     * @see https://man7.org/linux/man-pages/man2/bind.2.html
     */
    if (bind(server_socket.socket_fd, (struct sockaddr *)&server_socket.address,
             server_address_size) < 0) {
        log_err("Failed to bind the address with the server socket");
        close(server_socket.socket_fd);
        return -1;
    }

    return 0;
}

int connect_to_socket(struct socket_connection server_socket) {
    socklen_t server_address_size = sizeof(server_socket.address);

    /**
     * @brief initiate a connection on a socket
     * @see https://man7.org/linux/man-pages/man2/connect.2.html
     */
    if (connect(server_socket.socket_fd,
                (struct sockaddr *)&server_socket.address,
                server_address_size) < 0) {
        log_err("Failed to connect %s:%s", server_socket.socket_name.host,
                server_socket.socket_name.port);
        close(server_socket.socket_fd);
        return -1;
    }

    return 0;
}

int listen_to_socket(struct socket_connection server_socket,
                     unsigned int backlog) {
    /**
     * @brief listen for connections on the server socket
     * @see https://man7.org/linux/man-pages/man2/listen.2.html
     */
    int listen_status = listen(server_socket.socket_fd, backlog);
    if (listen_status < 0) {
        log_err("Failed to listen on %s:%s", server_socket.socket_name.host,
                server_socket.socket_name.port);
        close(server_socket.socket_fd);
        return -1;
    }

    return 0;
}
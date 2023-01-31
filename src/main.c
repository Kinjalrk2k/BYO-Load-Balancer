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

#include "../include/connection.h"
#include "../include/logging.h"
#include "../include/networking.h"
#include "../include/server.h"
#include "../include/threads.h"

int main(int argc, char *argv[]) {
    int new_connection, bytes_read;

    struct socket_connection client_socket, target_socket;

    // initializ the thread pool
    init_thread_pool();

    /* Create a listening socket */
    if (create_server(&client_socket, "127.0.0.1", 2209, 10) < 0) {
        perror("Failed to create the server");
        return 1;
    }

    connection_loop(client_socket);

    return 0;
}

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
#include "../include/health_check.h"
#include "../include/logging.h"
#include "../include/networking.h"
#include "../include/round_robin.h"
#include "../include/server.h"
#include "../include/target_group.h"
#include "../include/threads.h"

void configuration() {
    struct target_group target_group_foo = {
        "/foo/*", 1, NULL, NULL, 0, PTHREAD_MUTEX_INITIALIZER};
    struct target_backend serverA = {"serverA", "127.0.0.1", 5000, 1};
    struct target_backend serverB = {"serverB", "127.0.0.1", 5001, 1};
    struct target_backend serverC = {"serverC", "127.0.0.1", 5002, 1};
    struct target_backend serverD = {"serverD", "127.0.0.1", 5003, 1};
    struct target_backend serverE = {"serverE", "127.0.0.1", 5004, 1};

    insert_to_round_robin(&target_group_foo.round_robin_head, serverA);
    insert_to_round_robin(&target_group_foo.round_robin_head, serverB);
    insert_to_round_robin(&target_group_foo.round_robin_head, serverC);
    insert_to_round_robin(&target_group_foo.round_robin_head, serverD);
    insert_to_round_robin(&target_group_foo.round_robin_head, serverE);

    struct target_group target_group_bar = {
        "/bar/*", 2, NULL, NULL, 0, PTHREAD_MUTEX_INITIALIZER};
    struct target_backend serverF = {"serverF", "127.0.0.1", 5010, 1};
    struct target_backend serverG = {"serverG", "127.0.0.1", 5011, 1};

    insert_to_round_robin(&target_group_bar.round_robin_head, serverF);
    insert_to_round_robin(&target_group_bar.round_robin_head, serverG);

    target_group_list_sorted_insert(target_group_foo);
    target_group_list_sorted_insert(target_group_bar);
}

int main(int argc, char *argv[]) {
    struct socket_connection client_socket;

    configuration();

    // initialize the thread pool
    init_thread_pool();

    // initial health check and interval based health check thread
    health_check_all_target_groups();
    build_passive_health_check_thread();

        /* Create a listening socket */
    if (create_server(&client_socket, "127.0.0.1", 2209, 10) < 0) {
        perror("Failed to create the server");
        return 1;
    }

    connection_loop(client_socket);

    return 0;
}

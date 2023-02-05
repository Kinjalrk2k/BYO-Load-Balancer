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

#include "../include/config.h"
#include "../include/config_file.h"
#include "../include/connection.h"
#include "../include/env.h"
#include "../include/health_check.h"
#include "../include/logging.h"
#include "../include/networking.h"
#include "../include/round_robin.h"
#include "../include/server.h"
#include "../include/target_group.h"
#include "../include/threads.h"

int main(int argc, char *argv[]) {
    logger("[STARTUP] Initializing");
    struct socket_connection client_socket;

    // set up env vars
    logger("[STARTUP] Setup Environment");
    setup_env();

    // read configuration from file
    logger("[STARTUP] Reading Config file");
    read_config_file();

    // initialize the thread pool
    logger("[STARTUP] Initializing thread pools");
    init_thread_pool();

    // initial health check and interval based health check thread
    logger("[STARTUP] Setting up Health checks");
    health_check_all_target_groups();
    build_passive_health_check_thread();

    /* Create a listening socket */
    if (create_server(&client_socket, get_env_host(), get_env_port(),
                      get_env_backlog()) < 0) {
        log_err("Failed to create the server");
        return 1;
    }

    connection_loop(client_socket);

    return 0;
}

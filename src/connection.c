#include "../include/connection.h"

void *handle_connection(void *p_new_connection) {
    int new_connection = *((int *)p_new_connection);
    free(p_new_connection);

    struct socket_connection target_socket;
    int bytes_read;
    char buffer[BUFSIZE];

    /* Read the client's request */
    bytes_read = recv(new_connection, buffer, BUFSIZE - 1, 0);

    // get the next target
    struct target_backend target;
    if (handle_routing_target(buffer, &target, new_connection) == 1) {
        return NULL;
    }

    /* Create a target socket */
    if (connect_to_target(&target_socket, target.host, target.port) < 0) {
        handle_503(target_socket, new_connection);
        return NULL;
    }

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

// send 1 if already handled or else send 0, if sent -1, then mishandled
int handle_routing_target(char *request_buffer, struct target_backend *p_target,
                          int new_connection) {
    int already_handled = 0;  // return flag

    char *request_copy = (char *)malloc(strlen(request_buffer) + 1);
    strcpy(request_copy, request_buffer);
    char *url = parse_url(request_copy);

    // health report
    if (strcmp(url, "/__health") == 0) {
        logger("[ROUTE] %s => Health Report", url);
        handle_health_route(new_connection);
        return 1;  // already handled
    }

    struct target_group *tg;
    find_target_group_with_path(url, &tg);
    struct target_backend target;
    target = get_next_backend(tg->round_robin_head, &tg->round_robin_current,
                              tg->round_robin_mutex);

    // request logging
    logger("[ROUTE] %s ~~> %s => %s:%d <%d>", url, tg->path, target.host,
           target.port, target.is_healthy);

    *p_target = target;
    free(request_copy);
    return already_handled;
}

void handle_503(struct socket_connection target_socket, int new_connection) {
    char *html =
        "<!DOCTYPE html>"
        "<html lang=\"en\">"
        "<head>"
        "<title>503</title>"
        "</head>"
        "<body>"
        "<h1><center>Service Unavailable</center></h1>"
        "<h2><center>503</center></h2>"
        "</body>"
        "</html>";
    char response[16384] =
        "HTTP/1.1 503 Service unavailable\n\r"
        "Content-Type: text/html charset=utf-8\n\r"
        "\n\r";
    strcat(response, html);

    send(new_connection, response, strlen(response), 0);

    /* close sockets */
    close(target_socket.socket_fd);
    close(new_connection);
}

void handle_health_route(int new_connection) {
    char response[262144];

    char json[65536] = "";
    get_health_json(json);

    char json_length_str[5];
    sprintf(json_length_str, "%d", (int)strlen(json));

    add_status_code_to_response(response, "200", "HTTP/1.1");
    add_header_to_response(response, "Content-Type", "application/json");
    add_header_to_response(response, "Content-Length", json_length_str);
    add_content_to_response(response, json);

    send(new_connection, response, strlen(response), 0);
    close(new_connection);
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

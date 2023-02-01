#include "../include/connection.h"

void *handle_connection(void *p_new_connection) {
    int new_connection = *((int *)p_new_connection);
    free(p_new_connection);

    struct socket_connection target_socket;
    int bytes_read;
    char buffer[BUFSIZE];

    /* Read the client's request */
    bytes_read = recv(new_connection, buffer, BUFSIZE - 1, 0);

    // if (handle_health_check_report_route(buffer, new_connection) == 1) {
    //     return NULL;
    // }

    // get the next target
    // struct target_backend target = get_next_backend();

    /* Create a target socket */
    if (connect_to_target(&target_socket, "127.0.0.1", 5000) < 0) {
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

// // TODO: use malloc to use memory better
// // 1 - was a health report route , 1 - otherwise
// int handle_health_check_report_route(char *request_buffer, int
// new_connection) {
//     int flag = 0;  // return flag

//     char *request_copy = (char *)malloc(strlen(request_buffer) + 1);
//     strcpy(request_copy, request_buffer);
//     char *url = parse_url(request_copy);

//     if (strcmp(url, "/__health") == 0) {
//         flag = 1;

//         logger("Health report route called!");
//         const int response_buffer_size = 262144;  // 256 KB
//         char response[response_buffer_size];

//         char response_body[65536];
//         get_health_in_json(response_body);
//         char response_body_length_str[5];
//         sprintf(response_body_length_str, "%d", (int)strlen(response_body));

//         add_status_code_to_response(response, "200", "HTTP/1.1");
//         add_header_to_response(response, "Content-Type", "application/json");
//         add_header_to_response(response, "Content-Length",
//                                response_body_length_str);
//         add_content_to_response(response, response_body);

//         send(new_connection, response, sizeof(response), 0);
//     }

//     free(request_copy);
//     return flag;
// }
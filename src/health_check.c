#include "../include/health_check.h"

char *parse_status_code(char *response) {
    const char *seperator = " ";
    char *token = strtok(response, seperator);
    token = strtok(NULL, seperator);

    return token;
}

// 0 - unhealthy , 1 - healthy
int health_check_target(struct target_backend target) {
    struct socket_connection target_socket;
    char response[BUFSIZE];
    int bytes_read;

    int target_connect_status =
        connect_to_target(&target_socket, target.host, target.port);
    if (target_connect_status < 0) {
        return 0;
    }

    char *raw_health_check_request = "GET / HTTP/1.1\r\n\r\n";
    int send_status = send(target_socket.socket_fd, raw_health_check_request,
                           strlen(raw_health_check_request), 0);
    if (send_status < 0) {
        return 0;
    }

    (bytes_read = recv(target_socket.socket_fd, response, BUFSIZE - 1, 0));

    char *status_code = parse_status_code(response);
    if (strcmp(status_code, "200") != 0) {
        return 0;
    }

    close(target_socket.socket_fd);
    return 1;
}

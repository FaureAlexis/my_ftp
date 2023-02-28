/*
** EPITECH PROJECT, 2023
** server
** File description:
** ftp sertver
*/

#include <unistd.h>
#include "../../include/ftp.h"

void get_command_and_param(const char *input, char *command, char *param)
{
    char *input_copy = strdup(input);
    char *token = strtok(input_copy, " ");

    strcpy(command, token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        param = NULL;
        return;
    }
    strcpy(param, token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        return;
    }
    strcat(param, " ");
    strcat(param, token);
    while ((token = strtok(NULL, " ")) != NULL) {
        strcat(param, " ");
        strcat(param, token);
    }
    free(input_copy);
}

int bind_and_listen(
    ftp_t *ftp, int server_socket, struct sockaddr_in server_address)
{
    int bind_status = bind(server_socket, (struct sockaddr *) &server_address,
        sizeof(server_address));
    if (bind_status == -1) {
        perror("bind");
        return -1;
    }
    int listen_status = listen(server_socket, 5);
    if (listen_status == -1) {
        perror("listen");
        return -1;
    }
    return 0;
}

int configure_server(ftp_t *ftp)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        return -1;
    }
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(ftp->port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    if (bind_and_listen(ftp, server_socket, server_address) == -1)
        return -1;
    log_message(LOG_SUCCESS,
        "Server is successfully started and listening on port %s",
        ftp->port_str);
    return server_socket;
}

int handle_client_command(int client_socket, char *client_ip, char *command)
{
    char *cmd = malloc(strlen(command) + 1);
    char *param = malloc(strlen(command) + 1);
    get_command_and_param(command, cmd, param);

    if (strcmp(cmd, "QUIT") == 0) {
        write_client(client_socket, "221\n");
        log_message(LOG_WARNING, "%s: Disconnected", client_ip);
        close(client_socket);
        return 1;
    }
    if (strcmp(cmd, "NOOP") == 0) {
        write_client(client_socket, "200\n");
        return 0;
    }
    if (strcmp(cmd, "PWD") == 0) {
        if (pwd(client_socket) == 84)
            return 84;
        return 0;
    }
    if (strcmp(cmd, "CWD") == 0) {
        if (cwd(client_socket, param) == 84)
            return 84;
        return 0;
    }
    if (strcmp(cmd, "LS") == 0) {
        if (ls(client_socket) == 84)
            return 84;
        return 0;
    }
    if (strcmp(cmd, "CDUP") == 0) {
        if (cdup(client_socket) == 84)
            return 84;
        return 0;
    }
    write_client(client_socket, "500\n");
    return 0;
}

void handle_client_connection(int client_socket, char *client_ip)
{
    write_client(client_socket, "220\n");
    int login_status = login(client_socket);
    if (login_status == 84) {
        log_message(LOG_ERROR, "%s: Login failed", client_ip);
        close(client_socket);
        return;
    }
    log_message(LOG_SUCCESS, "%s: Logged in successfully", client_ip);
    while (1) {
        char *command = read_client(client_socket);
        if (command == NULL) {
            log_message(LOG_WARNING, "%s: Disconnected", client_ip);
            close(client_socket);
            return;
        }
        int ret = handle_client_command(client_socket, client_ip, command);
        free(command);
        if (ret == 1) {
            return;
        }
    }
}

int manage_connection(ftp_t *ftp)
{
    FD_ZERO(&ftp->read_fds);
    FD_SET(ftp->server_socket, &ftp->read_fds);
    ftp->max_clients = ftp->server_socket;

    bool used_clients[ftp->max_clients];
    memset(used_clients, false, sizeof used_clients);
    memset(ftp->client_sockets, 0, sizeof(int) * ftp->max_clients);
    if (!ftp->client_sockets) {
        perror("malloc");
        return 84;
    }
    for (int i = 0; i < ftp->max_clients; i += 1) {
        int cs_fd = 0;
        if (!ftp->client_sockets[i])
            continue;
        cs_fd = ftp->client_sockets[i];
        if (cs_fd > 0) {
            FD_SET(cs_fd, &ftp->read_fds);
        }
        if (cs_fd > ftp->max_clients) {
            ftp->max_clients = cs_fd;
        }
    }
    int ret = select(ftp->max_clients + 1, &ftp->read_fds, NULL, NULL, NULL);
    if (ret == -1) {
        perror("select");
        return 84;
    }
    if (FD_ISSET(ftp->server_socket, &ftp->read_fds)) {
        int client_socket = 0;
        struct sockaddr_in client_address;
        socklen_t client_address_len = sizeof(client_address);
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return 84;
        }
        if (pid == 0) {
            client_socket = accept(ftp->server_socket,
                (struct sockaddr *) &client_address, &client_address_len);
            if (client_socket == -1) {
                perror("accept");
                return 84;
            }
            char *client_ip = inet_ntoa(client_address.sin_addr);
            log_message(LOG_INFO, "%s: Connected", client_ip);
            handle_client_connection(client_socket, client_ip);
            exit(0);
        } else {
            close(client_socket);
        }
    }
    return 0;
}

int server(ftp_t *ftp)
{
    int server_socket = configure_server(ftp);
    if (server_socket == -1) {
        return 84;
    }
    ftp->server_socket = server_socket;
    ftp->max_clients = 5;
    ftp->client_sockets = NULL;
    ftp->client_sockets = malloc(sizeof(int) * ftp->max_clients);
    if (!ftp->client_sockets) {
        perror("malloc");
        return 84;
    }
    log_message(LOG_INFO, "Waiting for connections...");
    while (1) {
        manage_connection(ftp);
    }
    close(ftp->server_socket);
    return 0;
}

/*
** EPITECH PROJECT, 2023
** server
** File description:
** ftp sertver
*/

#include "../../include/ftp.h"

static int init_fds(ftp_t *ftp)
{
    FD_ZERO(&ftp->read_fds);
    FD_SET(ftp->server_socket, &ftp->read_fds);
    ftp->max_clients = ftp->server_socket;

    bool used_clients[ftp->max_clients];
    memset(used_clients, false, sizeof used_clients);
    memset(ftp->client_sockets, 0, sizeof(int) * ftp->max_clients);
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
    return 0;
}

static int wait_for_clients(ftp_t *ftp)
{
    int ret = select(ftp->max_clients + 1, &ftp->read_fds, NULL, NULL, NULL);
    if (ret == -1) {
        perror("select");
        return 84;
    }
    return 0;
}

static int handle_new_client(ftp_t *ftp)
{
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
        char *client_ip = inet_ntoa(client_address.sin_addr);
        log_message(LOG_INFO, "%s: Connected", client_ip);
        handle_client_connection(client_socket, client_ip);
        exit(0);
    } else {
        close(client_socket);
    }
    return 0;
}

static int manage_connection(ftp_t *ftp)
{
    if (init_fds(ftp) == 84) {
        return 84;
    }
    if (wait_for_clients(ftp) == 84) {
        return 84;
    }
    if (FD_ISSET(ftp->server_socket, &ftp->read_fds)) {
        if (handle_new_client(ftp) == 84) {
            return 84;
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

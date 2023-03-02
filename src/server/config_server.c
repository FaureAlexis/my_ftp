/*
** EPITECH PROJECT, 2023
** config server
** File description:
** ftp
*/

#include "../../include/ftp.h"

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

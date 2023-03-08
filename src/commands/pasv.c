/*
** EPITECH PROJECT, 2023
** pasv
** File description:
** ftp cmd
*/

#include "../../include/ftp.h"

int pasv(int client_socket)
{
    int port = 0;
    int pasv_socket = 0;
    int pasv_client_socket = 0;
    struct sockaddr_in pasv_server_address;
    struct sockaddr_in pasv_client_address;
    socklen_t pasv_client_address_size = sizeof(pasv_client_address);
    char *port_str = malloc(1024);
    char *pasv_str = malloc(1024);

    memset(port_str, 0, 1024);
    memset(pasv_str, 0, 1024);
    pasv_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (pasv_socket == -1) {
        perror("socket");
        return 84;
    }
    pasv_server_address.sin_family = AF_INET;
    pasv_server_address.sin_addr.s_addr = INADDR_ANY;
    pasv_server_address.sin_port = htons(0);
    if (bind(pasv_socket, (struct sockaddr *) &pasv_server_address,
            sizeof(pasv_server_address))
        < 0) {
        perror("bind");
        return 84;
    }
    if (listen(pasv_socket, 1) < 0) {
        perror("listen");
        return 84;
    }
    if (getsockname(pasv_socket, (struct sockaddr *) &pasv_server_address,
            &pasv_client_address_size)
        < 0) {
        perror("getsockname");
        return 84;
    }
    port = ntohs(pasv_server_address.sin_port);
    sprintf(port_str, "%d", port);
    sprintf(pasv_str, "227 Entering Passive Mode (%s,%s,%s)\r\n", "127.0.0.1",
        port_str, port_str);
    write_client(client_socket, pasv_str);
    pasv_client_socket = accept(pasv_socket,
        (struct sockaddr *) &pasv_client_address, &pasv_client_address_size);
    if (pasv_client_socket < 0) {
        perror("accept");
        return 84;
    }
    return pasv_client_socket;
}

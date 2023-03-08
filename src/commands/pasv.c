/*
** EPITECH PROJECT, 2023
** pasv
** File description:
** ftp cmd
*/

#include "../../include/ftp.h"

int create_pasv_socket(void)
{
    int pasv_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (pasv_socket == -1) {
        perror("socket");
        return -1;
    }
    struct sockaddr_in pasv_server_address = {0};
    pasv_server_address.sin_family = AF_INET;
    pasv_server_address.sin_addr.s_addr = INADDR_ANY;
    pasv_server_address.sin_port = htons(0);
    if (bind(pasv_socket, (struct sockaddr *) &pasv_server_address,
            sizeof(pasv_server_address))
        < 0) {
        perror("bind");
        return -1;
    }
    if (listen(pasv_socket, 1) < 0) {
        perror("listen");
        return -1;
    }
    return pasv_socket;
}

int get_pasv_port(int pasv_socket, char *port_str)
{
    struct sockaddr_in pasv_server_address = {0};
    socklen_t pasv_server_address_size = sizeof(pasv_server_address);
    if (getsockname(pasv_socket, (struct sockaddr *) &pasv_server_address,
            &pasv_server_address_size)
        < 0) {
        perror("getsockname");
        return -1;
    }
    int port = ntohs(pasv_server_address.sin_port);
    sprintf(port_str, "%d", port);
    return port;
}

int accept_pasv_client(int pasv_socket)
{
    struct sockaddr_in pasv_client_address = {0};
    socklen_t pasv_client_address_size = sizeof(pasv_client_address);
    int pasv_client_socket = accept(pasv_socket,
        (struct sockaddr *) &pasv_client_address, &pasv_client_address_size);
    if (pasv_client_socket < 0) {
        perror("accept");
        return -1;
    }
    return pasv_client_socket;
}

int pasv(int client_socket)
{
    char *port_str = malloc(1024);
    char *pasv_str = malloc(1024);
    memset(port_str, 0, 1024);
    memset(pasv_str, 0, 1024);
    int pasv_socket = create_pasv_socket();
    if (pasv_socket < 0) {
        return 84;
    }
    int port = get_pasv_port(pasv_socket, port_str);
    if (port < 0) {
        return 84;
    }
    sprintf(pasv_str, "227 Entering Passive Mode (%s,%s,%s)\r\n", "127.0.0.1",
        port_str, port_str);
    write_client(client_socket, pasv_str);
    int pasv_client_socket = accept_pasv_client(pasv_socket);
    if (pasv_client_socket < 0) {
        return 84;
    }
    return pasv_client_socket;
}

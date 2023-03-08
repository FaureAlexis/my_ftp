/*
** EPITECH PROJECT, 2023
** socket tools
** File description:
** ftp
*/

#include "../../include/ftp.h"

int create_socket(char *ip, int port)
{
    int data_socket = 0;
    struct sockaddr_in data_addr;

    data_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (data_socket == -1) {
        perror("socket");
        return 84;
    }
    data_addr.sin_family = AF_INET;
    data_addr.sin_port = htons(port);
    data_addr.sin_addr.s_addr = inet_addr(ip);
    if (connect(data_socket, (struct sockaddr *) &data_addr, sizeof(data_addr))
        == -1) {
        perror("connect");
        return 84;
    }
    return data_socket;
}

char *read_client(int client_socket, size_t size)
{
    char *buffer = malloc(size);
    memset(buffer, 0, size);
    int bytes_read = read(client_socket, buffer, size - 1);
    if (bytes_read < 0) {
        perror("read");
        free(buffer);
        return NULL;
    }
    return buffer;
}

int write_client(int client_socket, char *response)
{
    int bytes_sent = write(client_socket, response, strlen(response));
    if (bytes_sent == -1) {
        perror("write");
        return 84;
    }
    return 0;
}

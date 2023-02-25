/*
** EPITECH PROJECT, 2023
** socket tools
** File description:
** ftp
*/

#include "../../include/ftp.h"

char *read_client(int client_socket)
{
    char *buffer = malloc(1024);
    memset(buffer, 0, 1024);
    int bytes_read = read(client_socket, buffer, 1024 - 1);
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

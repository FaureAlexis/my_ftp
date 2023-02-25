/*
** EPITECH PROJECT, 2023
** pwd
** File description:
** return current location
*/

#include "../../include/ftp.h"

int pwd(int client_socket)
{
    char *path = malloc(1024);
    memset(path, 0, 1024);
    if (getcwd(path, 1024) == NULL) {
        perror("getcwd");
        free(path);
        return 84;
    }
    if (write_client(client_socket, "257 ") == 84)
        return 84;
    if (write_client(client_socket, path) == 84)
        return 84;
    if (write_client(client_socket, "\n") == 84)
        return 84;
    free(path);
    return 0;
}

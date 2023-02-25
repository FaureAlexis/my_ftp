/*
** EPITECH PROJECT, 2023
** cwd
** File description:
** cwd command
*/

#include "../../include/ftp.h"

int cwd(int client_socket, char *path)
{
    if (chdir(path) == -1) {
        perror("chdir");
        return 84;
    }
    if (write_client(client_socket, "250\n") == 84)
        return 84;
    return 0;
}

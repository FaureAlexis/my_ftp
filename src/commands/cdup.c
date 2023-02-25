/*
** EPITECH PROJECT, 2023
** cdup
** File description:
** cdup command
*/

#include "../../include/ftp.h"

int cdup(int client_socket)
{
    if (chdir("..") == -1) {
        perror("chdir");
        return 84;
    }
    if (write_client(client_socket, "250\n") == 84)
        return 84;
    return 0;
}

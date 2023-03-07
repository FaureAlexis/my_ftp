/*
** EPITECH PROJECT, 2023
** dele
** File description:
** dele cmd
*/

#include "../../include/ftp.h"

int dele(int client_socket, char *param)
{
    if (param == NULL) {
        if (write_client(client_socket, "550\n") == 84)
            return 84;
        return 0;
    }
    if (remove(param) == -1) {
        if (write_client(client_socket, "550\n") == 84)
            return 84;
        return 0;
    }
    if (write_client(client_socket, "250\n") == 84)
        return 84;
    return 0;
}

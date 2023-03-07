/*
** EPITECH PROJECT, 2023
** dele
** File description:
** ftp command
*/

#include "../../../include/ftp.h"

int handle_dele_command(int client_socket, char *param)
{
    if (dele(client_socket, param) == 84)
        return 84;
    return 0;
}

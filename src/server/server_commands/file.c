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

int handle_retr_command(int client_socket, char *param)
{
    if (retr(client_socket, param) == 84)
        return 84;
    return 0;
}

int handle_stor_command(int client_socket, char *param)
{
    if (stor(client_socket, param) == 84)
        return 84;
    return 0;
}

int handle_pasv_command(int client_socket, char *param)
{
    if (pasv(client_socket) == 84)
        return 84;
    return 0;
}

int handle_port_command(int client_socket, char *param)
{
    if (port(client_socket, param) == 84)
        return 84;
    return 0;
}

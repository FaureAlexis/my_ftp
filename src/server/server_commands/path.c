/*
** EPITECH PROJECT, 2023
** path
** File description:
** fpt
*/

#include "../../../include/ftp.h"

int handle_pwd_command(int client_socket, char *param)
{
    if (pwd(client_socket) == 84)
        return 84;
    return 0;
}

int handle_cwd_command(int client_socket, char *param)
{
    if (cwd(client_socket, param) == 84)
        return 84;
    return 0;
}

int handle_ls_command(int client_socket, char *param)
{
    if (myls(client_socket) == 84)
        return 84;
    return 0;
}

int handle_cdup_command(int client_socket, char *param)
{
    if (cdup(client_socket) == 84)
        return 84;
    return 0;
}

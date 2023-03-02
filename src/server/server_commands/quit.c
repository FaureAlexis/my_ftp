/*
** EPITECH PROJECT, 2023
** quit
** File description:
** ftp
*/

#include "../../../include/ftp.h"

int handle_quit_command(int client_socket, char *client_ip)
{
    write_client(client_socket, "221\n");
    log_message(LOG_WARNING, "%s: Disconnected", client_ip);
    close(client_socket);
    return 1;
}

int handle_noop_command(int client_socket)
{
    write_client(client_socket, "200\n");
    return 0;
}

int handle_help_command(int client_socket)
{
    write_client(client_socket, "214\n");
    return 0;
}

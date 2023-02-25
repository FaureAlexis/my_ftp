/*
** EPITECH PROJECT, 2023
** login
** File description:
** my ftp
*/

#include "../../include/ftp.h"

int login(int client_socket)
{
    char *userLine = NULL;
    char *passLine = NULL;
    char *username = NULL;
    char *password = NULL;

    userLine = read_client(client_socket);
    if (!userLine)
        return 84;
    username = strtok(userLine, "\r\n");
    username = strtok(username, " ");
    username = strtok(NULL, " ");
    if (!username)
        return 84;
    if (strcmp(username, "Anonymous") == 0) {
        if (write_client(client_socket, "331\n") == 84)
            return 84;
    } else {
        if (write_client(client_socket, "530\n") == 84)
            return 84;
        return 84;
    }
    passLine = read_client(client_socket);
    if (!passLine)
        return 84;
    password = strtok(passLine, "\r\n");
    password = strtok(password, " ");
    password = strtok(NULL, " ");
    if (!password && strcmp(username, "Anonymous") == 0) {
        if (write_client(client_socket, "230\n") == 84)
            return 84;
    } else {
        if (write_client(client_socket, "530\n") == 84)
            return 84;
        return 84;
    }
    return 0;
}

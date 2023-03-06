/*
** EPITECH PROJECT, 2023
** login
** File description:
** my ftp
*/

#include "../../include/ftp.h"

static int read_username(int client_socket, char **username)
{
    char *user_line = read_client(client_socket);
    if (!user_line)
        return 84;
    *username = strtok(user_line, "\r\n");
    *username = strtok(*username, " ");
    *username = strtok(NULL, " ");
    if (!*username)
        return 84;
    return 0;
}

static int write_login_success(int client_socket)
{
    if (write_client(client_socket, "230\n") == 84)
        return 84;
    return 0;
}

static int write_login_failure(int client_socket)
{
    if (write_client(client_socket, "530\n") == 84)
        return 84;
    return 84;
}

static int check_auth(
    char *password, char *pass_line, int client_socket, char *username)
{
    if (!pass_line)
        return 84;
    password = strtok(pass_line, "\r\n");
    password = strtok(password, " ");
    printf("%s\n", password);
    if (!password || strcmp(password, "PASS") != 0) {
        if (write_login_failure(client_socket) == 84)
            return 84;
        return 84;
    }
    password = strtok(NULL, " ");
    if (!password && strcmp(username, "Anonymous") == 0) {
        if (write_login_success(client_socket) == 84)
            return 84;
    } else {
        if (write_login_failure(client_socket) == 84)
            return 84;
        return 84;
    }
    return 0;
}

int login(int client_socket)
{
    char *username = NULL;
    int ret = read_username(client_socket, &username);
    if (ret == 84)
        return 84;
    if (strcmp(username, "Anonymous") == 0) {
        if (write_client(client_socket, "331\n") == 84)
            return 84;
    } else {
        if (write_client(client_socket, "331\n") == 84)
            return 84;
        return 84;
    }
    char *password = NULL;
    char *pass_line = read_client(client_socket);
    return check_auth(password, pass_line, client_socket, username);
}

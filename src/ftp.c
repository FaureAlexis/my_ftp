/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** ftp server
*/

#include "../include/ftp.h"

ftp_t *ftp;

int free_all(ftp_t *ftp, int code)
{
    if (ftp->client_sockets)
        free(ftp->client_sockets);
    if (ftp->home_fd) {
        closedir(ftp->home_fd);
        free(ftp->home);
    }
    free(ftp);
    return code;
}

void sigint_handler(int sig)
{
    (void) sig;
    free_all(ftp, 0);
    exit(0);
}

int myftp(const char *port, const char *home)
{
    ftp = malloc(sizeof(ftp_t));
    if (!ftp)
        return 84;
    ftp->port = atoi(port);
    ftp->port_str = port;
    ftp->max_clients = 0;
    if (check_home(ftp, home) == 84)
        return free_all(ftp, 84);
    signal(SIGINT, sigint_handler);
    if (chdir(ftp->home) == -1) {
        perror("chdir");
        return 84;
    }
    server(ftp);
    return free_all(ftp, 0);
}

/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** ftp server
*/

#include "../include/ftp.h"

ftp_t *ftp;

int free_all(void)
{
    if (ftp->client_sockets)
        free(ftp->client_sockets);
    if (ftp->home_fd) {
        closedir(ftp->home_fd);
        free(ftp->home);
    }
    free(ftp);
    return 0;
}

void sigint_handler(int sig)
{
    (void) sig;
    free_all();
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
        return free_all();
    signal(SIGINT, sigint_handler);
    server(ftp);
    return free_all();
}

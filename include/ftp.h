/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** header
*/

#ifndef FTP_H
#define FTP_H
#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "auth.h"
#include "logger.h"

typedef struct ftp_s {
    int server_socket;
    int port;
    const char *port_str;
    int max_clients;
    char *home;
    DIR *home_fd;
    fd_set read_fds;
    int *client_sockets;
} ftp_t;

/* FTP */
int myftp(const char *port, const char *home);

/* Server */
int server(ftp_t *ftp);

/* FS */
int check_if_home_exist(ftp_t *ftp);
int check_if_home_is_dir(ftp_t *ftp);
int check_if_home_is_readable(ftp_t *ftp);
int check_if_home_is_writable(ftp_t *ftp);
int check_home(ftp_t *ftp, const char *home);

/* Commands */
int pwd(int client_socket);
int cwd(int client_socket, char *path);
int ls(int client_socket);
int cdup(int client_socket);

/* Socket tools */
int write_client(int client_socket, char *response);
char *read_client(int client_socket);

int free_all(ftp_t *ftp, int code);
#endif /* !FTP_H */

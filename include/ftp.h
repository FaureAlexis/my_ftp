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

typedef int (*command_handler_t)(int, char *);
/* FTP */
int myftp(const char *port, const char *home);

/* Server */
int server(ftp_t *ftp);
int configure_server(ftp_t *ftp);
int bind_and_listen(
    ftp_t *ftp, int server_socket, struct sockaddr_in server_address);

void get_command_and_param(const char *input, char *command, char *param);
void remove_cr(char *str);

void handle_client_connection(int client_socket, char *client_ip);
int handle_client_command(int client_socket, char *client_ip, char *command);
int login(int client_socket);
int handle_quit_command(int client_socket, char *client_ip);
int handle_noop_command(int client_socket);
int handle_pwd_command(int client_socket);
int handle_cwd_command(int client_socket, char *param);
int handle_ls_command(int client_socket);
int handle_cdup_command(int client_socket);
int handle_help_command(int client_socket);
int handle_dele_command(int client_socket, char *param);
int handle_retr_command(int client_socket, char *param);
int port(int client_socket, char *param);
int retr(int client_socket, char *param);

/* FS */
int check_if_home_exist(ftp_t *ftp);
int check_if_home_is_dir(ftp_t *ftp);
int check_if_home_is_readable(ftp_t *ftp);
int check_if_home_is_writable(ftp_t *ftp);
int check_home(ftp_t *ftp, const char *home);

/* Commands */
int pwd(int client_socket);
int cwd(int client_socket, char *path);
int myls(int client_socket);
int cdup(int client_socket);
int dele(int client_socket, char *param);

/* Socket tools */
int write_client(int client_socket, char *response);
char *read_client(int client_socket);
int create_socket(char *ip, int port);

int free_all(ftp_t *ftp, int code);
#endif /* !FTP_H */

/*
** EPITECH PROJECT, 2023
** auth
** File description:
** ftp
*/

#ifndef AUTH_H
#define AUTH_H

typedef enum permissions_e { READ = 0, WRITE = 1, EXEC = 2 } permissions_t;

typedef struct user_s {
    char *username;
    char *password;
    char *pwd_salt;
    char *home;
    char *last_dir;
    int logged;
    int fd;
    permissions_t permissions;
} user_t;

int login(int client_socket);
#endif /* !AUTH_H */

/*
** EPITECH PROJECT, 2023
** ls
** File description:
** ls command
*/

#include "../../include/ftp.h"

int ls(int client_socket)
{
    char *path = malloc(1024);
    memset(path, 0, 1024);
    if (getcwd(path, 1024) == NULL) {
        perror("getcwd");
        free(path);
        return 84;
    }
    if (fork() == 0) {
        dup2(client_socket, 1);
        execl("/bin/ls", "ls", "-l", path, NULL);
        exit(0);
    }
    wait(NULL);
    free(path);
    return 0;
}

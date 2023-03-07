/*
** EPITECH PROJECT, 2023
** retr
** File description:
** ftp cmd
*/

#include "../../include/ftp.h"

size_t get_file_size(char *path)
{
    struct stat st;

    stat(path, &st);
    return st.st_size;
}

int retr(int client_socket, char *param)
{
    int fd = open(param, O_RDONLY);
    size_t size_file = get_file_size(param);
    char *buffer = malloc(size_file);
    int size = 0;

    if (fd == -1) {
        if (write_client(client_socket, "550\n") == 84)
            return 84;
        return 0;
    }
    if (write_client(client_socket, "150\n") == 84)
        return 84;
    while ((size = read(fd, buffer, size_file)) > 0) {
        if (write_client(client_socket, buffer) == 84)
            return 84;
    }
    if (write_client(client_socket, "226\n") == 84)
        return 84;
    return 0;
}

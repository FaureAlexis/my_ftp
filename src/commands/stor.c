/*
** EPITECH PROJECT, 2023
** stor
** File description:
** ftp cmd
*/

#include "../../include/ftp.h"

int stor(int client_socket, char *param)
{
    if (param == NULL)
        write_client(client_socket, "550\n");
    if (write_client(client_socket, "150\n") == 84)
        return 84;
    FILE *file = fopen(param, "wb");
    if (file == NULL) {
        fprintf(stderr, "Error: could not open file for writing\n");
        return 84;
    }
    char *buffer = read_client(client_socket, 4096);
    if (buffer == NULL) {
        fprintf(stderr, "Error: could not read from client\n");
        return 84;
    }
    fwrite(buffer, 1, strlen(buffer), file);
    fclose(file);
    if (write_client(client_socket, "226\n") == 84)
        return 84;
    return 0;
}

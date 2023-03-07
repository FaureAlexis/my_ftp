/*
** EPITECH PROJECT, 2023
** port
** File description:
** ftp cmd
*/

#include "../../include/ftp.h"

static char **my_str_to_word_array(char *str, char separator)
{
    char **arr = NULL;
    int i = 0;
    int j = 0;
    int k = 0;
    arr = malloc(sizeof(char *) * (strlen(str) + 1));
    if (arr == NULL)
        return NULL;
    for (; str[i] != '\0'; i++) {
        for (j = 0; str[i] != separator && str[i] != '\0'; j++, i++)
            ;
        arr[k] = malloc(sizeof(char) * (j + 1));
        if (arr[k] == NULL)
            return NULL;
        for (j = 0; str[i] != separator && str[i] != '\0'; j++, i++)
            arr[k][j] = str[i];
        arr[k][j] = '\0';
        k++;
    }
    arr[k] = NULL;
    return arr;
}

int port(int client_socket, char *param)
{
    char **ip = NULL;
    int port = 0;
    int data_socket = 0;

    if (param == NULL) {
        if (write_client(client_socket, "550\n") == 84)
            return 84;
        return 0;
    }
    ip = my_str_to_word_array(param, ',');
    if (ip == NULL)
        return 84;
    port = (atoi(ip[4]) * 256) + atoi(ip[5]);
    data_socket = create_socket(ip[0], port);
    if (data_socket == 84)
        return 84;
    if (write_client(client_socket, "200\n") == 84)
        return 84;
    return data_socket;
}

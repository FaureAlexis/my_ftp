/*
** EPITECH PROJECT, 2023
** server tools
** File description:
** ftp
*/

#include "../../include/ftp.h"

void get_command_and_param(const char *input, char *command, char *param)
{
    char *input_copy = strdup(input);
    char *token = strtok(input_copy, " ");
    strcpy(command, token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        param = NULL;
        return;
    }
    strcpy(param, token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        return;
    }
    strcat(param, " ");
    strcat(param, token);
    while ((token = strtok(NULL, " ")) != NULL) {
        strcat(param, " ");
        strcat(param, token);
    }
    free(input_copy);
}

/*
** EPITECH PROJECT, 2023
** server funcs
** File description:
** ftp
*/

#include "../../include/ftp.h"

const char *COMMANDS[] = {"QUIT", "NOOP", "PWD", "CWD", "LIST", "CDUP", "HELP",
    "DELE", "RETR", "STOR", NULL};
command_handler_t COMMAND_HANDLERS[] = {handle_quit_command,
    handle_noop_command, handle_pwd_command, handle_cwd_command,
    handle_ls_command, handle_cdup_command, handle_help_command,
    handle_dele_command, handle_retr_command, handle_stor_command, NULL};

int handle_client_command(int client_socket, char *client_ip, char *command)
{
    char *cmd = malloc(strlen(command) + 1);
    char *param = malloc(strlen(command) + 1);
    remove_cr(command);
    get_command_and_param(command, cmd, param);

    int i = 0;
    while (COMMANDS[i]) {
        if (strcmp(cmd, COMMANDS[i]) == 0) {
            int ret = COMMAND_HANDLERS[i](client_socket, param);
            free(cmd);
            free(param);
            return ret;
        }
        i++;
    }
    write_client(client_socket, "500\n");
    free(cmd);
    free(param);
    return 0;
}

int handle_client_login(int client_socket, char *client_ip)
{
    int login_status = login(client_socket);
    if (login_status == 84) {
        log_message(LOG_ERROR, "%s: Login failed", client_ip);
        close(client_socket);
        return 84;
    }
    return 0;
}

void handle_client_connection(int client_socket, char *client_ip)
{
    write_client(client_socket, "220\n");
    if (handle_client_login(client_socket, client_ip) == 84)
        return;
    log_message(LOG_SUCCESS, "%s: Logged in successfully", client_ip);
    while (1) {
        char *command = read_client(client_socket, 1024);
        if (command == NULL) {
            log_message(LOG_WARNING, "%s: Disconnected", client_ip);
            close(client_socket);
            return;
        }
        int ret = handle_client_command(client_socket, client_ip, command);
        free(command);
        if (ret == 1) {
            return;
        }
    }
}

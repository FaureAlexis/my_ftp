/*
** EPITECH PROJECT, 2023
** client
** File description:
** client
*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct client_s {
    int socket;
    struct sockaddr_in address;
    int server_port;
    char *server_ip;
} client_t;

int configure_client(client_t *client)
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket");
        return 84;
    }
    client->socket = client_socket;
    client->address.sin_family = AF_INET;
    client->address.sin_port = htons(client->server_port);
    client->address.sin_addr.s_addr = inet_addr(client->server_ip);
    int connect_status = connect(client_socket,
        (struct sockaddr *) &client->address, sizeof(client->address));
    if (connect_status == -1) {
        perror("connect");
        return 84;
    }
    // read server welcome message
    char buffer[1024] = {0};
    ssize_t r = read(client->socket, buffer, 1024);
    if (r == -1) {
        perror("read");
        return 84;
    }
    if (strcmp(buffer, "220\n") == 0) {
        printf("Connected to server\n");
    } else {
        printf("Connection failed\n");
        return 84;
    }
    return 0;
}

int handle_return_code(int return_code)
{
    if (return_code == 230)
        printf("Login successful\n");
    if (return_code == 530)
        printf("Login failed\n");
    if (return_code == 221)
        printf("Disconnected from server\n");
    return return_code;
}

int client_prompt(client_t *client)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t r;
    int last_return_code = 0;
    bool logged_in = false;
    while (1) {
        handle_return_code(last_return_code);
        if (last_return_code == 230)
            logged_in = true;
        if (last_return_code == 221)
            return 0;
        if (logged_in)
            printf("Anonymous@%s> ", client->server_ip);
        else
            printf("ftp@%s> ", client->server_ip);
        r = getline(&line, &len, stdin);
        if (r == -1) {
            close(client->socket);
            return 0;
        }
        line[r - 1] = '\0';
        if (strcmp(line, "quit") == 0) {
            close(client->socket);
            return 0;
        }
        write(client->socket, line, strlen(line));
        char buffer[1024] = {0};
        r = read(client->socket, buffer, 1024);
        if (r == -1) {
            perror("read");
            return 84;
        }
        printf("%s", buffer);
        last_return_code = atoi(buffer);
    }
    return 0;
}

int client_loop(char *host, char *port)
{
    client_t *client = malloc(sizeof(client_t));
    client->server_port = atoi(port);
    client->server_ip = host;
    if (configure_client(client) == 84)
        return 84;
    return client_prompt(client);
}

int main(int ac, char **av)
{
    if (ac != 3)
        return 84;
    return client_loop(av[1], av[2]);
}

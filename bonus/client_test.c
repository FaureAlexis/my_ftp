#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define USERNAME "Anonymous"
#define PASS     ""
#define TIMEOUT  1
#define OUT_SIZE 1024
#define CMD_SIZE 1024

void print_failed(char *test_name, int code)
{
    printf("%s test failed\n", test_name);
    printf("Expected reply-code: %d\n", code);
    printf("KO\n");
}

int launch_client(char *host, int port, int *client_socket)
{
    struct sockaddr_in server_address;

    *client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (*client_socket == -1) {
        perror("socket");
        return 84;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(host);

    int connect_status = connect(*client_socket,
        (struct sockaddr *) &server_address, sizeof(server_address));
    if (connect_status == -1) {
        perror("connect");
        return 84;
    }

    sleep(TIMEOUT);
    char buffer[OUT_SIZE];
    int n = read(*client_socket, buffer, OUT_SIZE);
    if (n == -1) {
        perror("read");
        return 0;
    }
    buffer[n] = '\0';
    printf("Server response: %s\n", buffer);
    if (n > 3 && buffer[0] == '2' && buffer[1] == '2' && buffer[2] == '0') {
        return 1;
    } else {
        return 0;
    }
}

int launch_test(char *test_name, char *cmd, int code, int client_socket)
{
    printf("Sending [%s^M]\n", cmd);
    write(client_socket, cmd, strlen(cmd));
    write(client_socket, "\r\n", 2);
    sleep(TIMEOUT);
    char buffer[OUT_SIZE];
    int n = read(client_socket, buffer, OUT_SIZE);
    if (n == -1) {
        perror("read");
        return 0;
    }
    buffer[n] = '\0';
    printf("Server response: %s\n", buffer);
    if (n < 3 || buffer[0] != code / 100 + '0'
        || buffer[1] != code % 100 / 10 + '0'
        || buffer[2] != code % 10 + '0') {
        print_failed(test_name, code);
        return -1;
    }
    printf("%s test succeeded\n", test_name);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("USAGE: %s host port\n", argv[0]);
        return 0;
    }
    char *host = argv[1];
    printf("Connecting to %s:%s\n", host, argv[2]);
    int port = atoi(argv[2]);
    int client_socket;
    int tests_failed = 0;
    if (!launch_client(host, port, &client_socket)) {
        return 84;
    }
    char buffer[1024];
    char userLine[CMD_SIZE];
    char passLine[CMD_SIZE];
    snprintf(userLine, sizeof(userLine), "USER %s", USERNAME);
    snprintf(passLine, sizeof(passLine), "PASS %s", PASS);

    int test1 = launch_test("Authentication", userLine, 331, client_socket);
    int test2 = launch_test("Authentication", passLine, 230, client_socket);

    if (test1 == -1 || test2 == -1) {
        tests_failed++;
    }
    close(client_socket);
    printf("Tests failed: %d\n", tests_failed);
    if (tests_failed > 0) {
        return 84;
    }
    return 0;
}

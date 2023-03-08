/*
** EPITECH PROJECT, 2023
** test server config
** File description:
** test ftp
*/

#include "../tests.h"

Test(bind_and_listen, test_valid_server_address, .init = redirect_all_std)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    ftp->port = 1234;
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(ftp->port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    cr_assert_eq(
        bind_and_listen(ftp, server_socket, server_address), 0, "Expected 0");
}

Test(configure_server, test_valid_server_configuration,
    .init = redirect_all_std)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    ftp->port = 1234;
    cr_assert_neq(configure_server(ftp), -1, "Expected return value != -1");
}

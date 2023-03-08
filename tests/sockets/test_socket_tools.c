/*
** EPITECH PROJECT, 2023
** test_socket
** File description:
** test tools
*/

#include "../tests.h"

Test(socket_tools, read_client, .init = redirect_all_std)
{
    int fd = open("tests/test_files/read", O_RDONLY);
    char *buffer = read_client(fd, 1024);
    cr_assert_str_eq(buffer, "test\n");
}

Test(socket_tools, wrong_fd, .init = redirect_all_std)
{
    char *buffer = read_client(45, 1024);
    cr_assert_eq(buffer, NULL);
}

Test(create_socket, test_valid_ip_and_port, .init = redirect_all_std)
{
    char *ip = "127.0.0.1";
    int port = 2121;
    cr_assert_eq(create_socket(ip, port), 84, "Expected return value != 0");
}

Test(create_socket, test_invalid_ip, .init = redirect_all_std)
{
    char *ip = "invalid_ip";
    int port = 2121;
    cr_assert_eq(create_socket(ip, port), 84, "Expected return value: 84");
}

Test(create_socket, test_invalid_port, .init = redirect_all_std)
{
    char *ip = "127.0.0.1";
    int port = 99999;
    cr_assert_eq(create_socket(ip, port), 84, "Expected return value: 84");
}

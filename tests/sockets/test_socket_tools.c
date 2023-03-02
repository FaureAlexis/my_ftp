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
    char *buffer = read_client(fd);
    cr_assert_str_eq(buffer, "test\n");
}

Test(socket_tools, wrong_fd, .init = redirect_all_std)
{
    char *buffer = read_client(45);
    cr_assert_eq(buffer, NULL);
}

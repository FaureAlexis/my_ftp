/*
** EPITECH PROJECT, 2023
** test login
** File description:
** test ftp
*/

#include "../../tests.h"

Test(write_login_success, test_login_success, .init = redirect_all_std)
{
    int client_socket = 1;
    cr_assert_eq(
        write_login_success(client_socket), 0, "Expected return value: 0");
    cr_assert_stdout_eq_str("230\n");
}

Test(write_login_failure, test_login_failure, .init = redirect_all_std)
{
    int client_socket = 1;
    cr_assert_eq(
        write_login_failure(client_socket), 84, "Expected return value: 84");
    cr_assert_stdout_eq_str("530\n");
}

Test(read_username, test_invalid_user_line, .init = redirect_all_std)
{
    int client_socket = 1;
    char *username = NULL;
    printf("USER noop\r\n");
    cr_assert_eq(read_username(client_socket, &username), 84,
        "Expected return value: 84");
}

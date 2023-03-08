/*
** EPITECH PROJECT, 2023
** test server tools
** File description:
** test ftp
*/

#include "../tests.h"

Test(remove_cr, test_valid_input)
{
    char str[] = "Hello\r\n";
    remove_cr(str);
    cr_assert_str_eq(str, "Hello", "Expected string: 'Hello'");
}

Test(remove_cr, test_input_with_multiple_cr)
{
    char str[] = "Hello\r\nWorld\r\n";
    remove_cr(str);
    cr_assert_str_eq(str, "HelloWorld", "Expected string: 'HelloWorld'");
}

Test(get_command_and_param, test_valid_input)
{
    const char *input = "LIST -l";
    char command[5];
    char param[1024];
    get_command_and_param(input, command, param);
    cr_assert_str_eq(command, "LIST", "Expected command: 'LIST'");
    cr_assert_str_eq(param, "-l", "Expected param: '-l'");
}

Test(get_command_and_param, test_input_with_multiple_spaces)
{
    const char *input = "   LIST    -l   ";
    char command[5];
    char param[1024];
    get_command_and_param(input, command, param);
    cr_assert_str_eq(command, "LIST", "Expected command: 'LIST'");
    cr_assert_str_eq(param, "-l", "Expected param: '-l'");
}

Test(get_command_and_param, test_multiples_params)
{
    const char *input = "LIST -l -a -h";
    char command[5];
    char param[1024];
    get_command_and_param(input, command, param);
    cr_assert_str_eq(command, "LIST", "Expected command: 'LIST'");
    cr_assert_str_eq(param, "-l -a -h", "Expected param: '-l -a -h'");
}

/*
** EPITECH PROJECT, 2023
** test pwd
** File description:
** tests
*/

#include <criterion/criterion.h>
#include "../../include/ftp.h"

Test(pwd, Basic_test)
{
    cr_assert_eq(pwd(1), 0);
}

Test(pwd, wrong_fd)
{
    cr_assert_eq(pwd(-1), 84);
}

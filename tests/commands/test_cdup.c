/*
** EPITECH PROJECT, 2023
** test cdup
** File description:
** tests
*/

#include <criterion/criterion.h>
#include "../../include/ftp.h"

Test(cdup, Basic_test)
{
    cr_assert_eq(cdup(1), 0);
}

Test(cdup, wrong_fd)
{
    cr_assert_eq(cdup(0), 84);
}

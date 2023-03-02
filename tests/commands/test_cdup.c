/*
** EPITECH PROJECT, 2023
** test cdup
** File description:
** tests
*/

#include "../tests.h"

Test(cdup, Basic_test, .init = redirect_all_std)
{
    cr_assert_eq(cdup(1), 0);
}

Test(cdup, wrong_fd, .init = redirect_all_std)
{
    cr_assert_eq(cdup(0), 84);
}

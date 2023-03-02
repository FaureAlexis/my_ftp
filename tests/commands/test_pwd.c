/*
** EPITECH PROJECT, 2023
** test pwd
** File description:
** tests
*/

#include "../tests.h"

Test(pwd, Basic_test, .init = redirect_all_std)
{
    cr_assert_eq(pwd(1), 0);
}

Test(pwd, wrong_fd, .init = redirect_all_std)
{
    cr_assert_eq(pwd(-1), 84);
}

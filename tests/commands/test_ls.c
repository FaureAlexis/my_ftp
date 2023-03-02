/*
** EPITECH PROJECT, 2023
** test ls
** File description:
** tests
*/

#include "../tests.h"

Test(ls, Basic_test, .init = redirect_all_std)
{
    cr_assert_eq(myls(1), 0);
}

/*
** EPITECH PROJECT, 2023
** test cwd
** File description:
** tests
*/

#include "../tests.h"

Test(cwd, Basic_test, .init = redirect_all_std)
{
    cr_assert_eq(cwd(1, "tests"), 0);
}

Test(cwd, Fake_dir, .init = redirect_all_std)
{
    cr_assert_eq(cwd(1, "fake"), 84);
}

Test(cwd, wrong_fd, .init = redirect_all_std)
{
    cr_assert_eq(cwd(0, "tests"), 84);
}

/*
** EPITECH PROJECT, 2023
** test cwd
** File description:
** tests
*/

#include <criterion/criterion.h>
#include "../../include/ftp.h"

Test(cwd, Basic_test)
{
    cr_assert_eq(cwd(1, "tests"), 0);
}

Test(cwd, Fake_dir)
{
    cr_assert_eq(cwd(1, "fake"), 84);
}

Test(cwd, wrong_fd)
{
    cr_assert_eq(cwd(0, "tests"), 84);
}

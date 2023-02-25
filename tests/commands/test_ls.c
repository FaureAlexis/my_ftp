/*
** EPITECH PROJECT, 2023
** test ls
** File description:
** tests
*/

#include <criterion/criterion.h>
#include "../../include/ftp.h"

Test(ls, Basic_test)
{
    cr_assert_eq(ls(1), 0);
}

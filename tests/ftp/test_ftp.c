/*
** EPITECH PROJECT, 2023
** test ftp
** File description:
** test
*/

#include <criterion/criterion.h>
#include "../../include/ftp.h"

Test(ftp, test_ftp)
{
    cr_assert_eq(myftp("21", "bonus"), 0);
}

Test(ftp, test_wrong_home)
{
    cr_assert_eq(myftp("21", "wrong"), 84);
}

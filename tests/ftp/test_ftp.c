/*
** EPITECH PROJECT, 2023
** test ftp
** File description:
** test
*/

#include "../tests.h"

Test(ftp, test_ftp, .init = redirect_all_std)
{
    cr_assert_eq(myftp("21", "bonus"), 0);
}

Test(ftp, test_wrong_home, .init = redirect_all_std)
{
    cr_assert_eq(myftp("21", "wrong"), 84);
}

/*
** EPITECH PROJECT, 2023
** test home func
** File description:
** test
*/

#include "../tests.h"

Test(home, home_is_dir_wrong, .init = redirect_all_std)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    ftp->home = "no";
    cr_assert_eq(check_if_home_is_dir(ftp), 84);
}

Test(home, home_dir_not_readable, .init = redirect_all_std)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    ftp->home = "tests/test_files/no";
    cr_assert_eq(check_if_home_is_readable(ftp), 84);
}

Test(home, home_dir_not_writable, .init = redirect_all_std)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    ftp->home = "tests/test_files/no";
    cr_assert_eq(check_if_home_is_writable(ftp), 84);
}

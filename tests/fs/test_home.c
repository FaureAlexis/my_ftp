/*
** EPITECH PROJECT, 2023
** test home
** File description:
** test ftp
*/

#include <criterion/criterion.h>
#include "../../include/ftp.h"

Test(home, home)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    cr_assert_eq(check_home(ftp, "client"), 0);
}

Test(home, wrong_home)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    cr_assert_eq(check_home(ftp, "no"), 84);
}

Test(home, home_not_dir)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    cr_assert_eq(check_home(ftp, "Makefile"), 84);
}

Test(home, test_fd)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    check_home(ftp, "no");
    cr_assert_eq(ftp->home_fd, NULL);
}

Test(home, test_good_fd)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    check_home(ftp, "client");
    cr_assert_neq(ftp->home_fd, NULL);
}

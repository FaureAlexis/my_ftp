/*
** EPITECH PROJECT, 2023
** test home
** File description:
** test ftp
*/

#include "../tests.h"

Test(home, home, .init = redirect_all_std)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    cr_assert_eq(check_home(ftp, "bonus"), 0);
}

Test(home, wrong_home, .init = redirect_all_std)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    cr_assert_eq(check_home(ftp, "no"), 84);
}

Test(home, home_not_dir, .init = redirect_all_std)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    cr_assert_eq(check_home(ftp, "Makefile"), 84);
}

Test(home, test_fd, .init = redirect_all_std)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    check_home(ftp, "no");
    cr_assert_eq(ftp->home_fd, NULL);
}

Test(home, test_good_fd, .init = redirect_all_std)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    check_home(ftp, "bonus");
    cr_assert_neq(ftp->home_fd, NULL);
}

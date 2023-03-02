/*
** EPITECH PROJECT, 2023
** test free
** File description:
** test ftp
*/

#include <dirent.h>
#include "../tests.h"

Test(free, test_free, .init = redirect_all_std)
{
    ftp_t *ftp = malloc(sizeof(ftp_t));
    ftp->client_sockets = malloc(sizeof(int) * 10);
    ftp->home = malloc(sizeof(char) * 10);
    ftp->home_fd = opendir("tests");
    cr_assert_eq(free_all(ftp, 0), 0);
}

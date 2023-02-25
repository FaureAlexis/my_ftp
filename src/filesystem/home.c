/*
** EPITECH PROJECT, 2023
** home
** File description:
** ftp server
*/

#include <dirent.h>
#include <sys/fcntl.h>
#include "../../include/ftp.h"

int check_if_home_exist(ftp_t *ftp)
{
    if (access(ftp->home, F_OK) == -1) {
        perror(ftp->home);
        return 84;
    }
    return 0;
}

int check_if_home_is_dir(ftp_t *ftp)
{
    struct stat sb;

    if (stat(ftp->home, &sb) == -1) {
        perror(ftp->home);
        return 84;
    }
    if (!S_ISDIR(sb.st_mode)) {
        fprintf(stderr, "%s is not a directory", ftp->home);
        return 84;
    }
    return 0;
}

int check_if_home_is_readable(ftp_t *ftp)
{
    if (access(ftp->home, R_OK) == -1) {
        perror(ftp->home);
        return 84;
    }
    return 0;
}

int check_if_home_is_writable(ftp_t *ftp)
{
    if (access(ftp->home, W_OK) == -1) {
        perror(ftp->home);
        return 84;
    }
    return 0;
}

int check_home(ftp_t *ftp, const char *home)
{
    ftp->home = NULL;
    ftp->home = malloc(sizeof(char) * (strlen(home) + 1));
    ftp->home = strcpy(ftp->home, home);
    ftp->home_fd = NULL;
    if (check_if_home_exist(ftp) == 84)
        return 84;
    if (check_if_home_is_dir(ftp) == 84)
        return 84;
    if (check_if_home_is_readable(ftp) == 84)
        return 84;
    if (check_if_home_is_writable(ftp) == 84)
        return 84;
    ftp->home_fd = opendir(ftp->home);
    if (ftp->home_fd == NULL) {
        perror(ftp->home);
        return 84;
    }
    return 0;
}

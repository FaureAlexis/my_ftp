/*
** EPITECH PROJECT, 2023
** main
** File description:
** my ftyp
*/

#include "../include/ftp.h"

int main(int ac, const char *const av[])
{
    if (ac != 3)
        return 84;
    return myftp(av[1], av[2]);
}

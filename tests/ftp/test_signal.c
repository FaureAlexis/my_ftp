/*
** EPITECH PROJECT, 2023
** test
** File description:
** test signal
*/

#include <criterion/criterion.h>
#include "../../include/ftp.h"

Test(fpt, test_signal_handler)
{
    pid_t pid = fork();

    if (pid == 0) {
        int ret = myftp("4242", "bonus");
        _exit(ret);
    } else if (pid > 0) {
        sleep(1);
        kill(pid, SIGINT);
        int status;
        waitpid(pid, &status, 0);
        int child_ret = WEXITSTATUS(status);
        cr_assert_eq(child_ret, 0);
    } else {
        cr_assert_fail();
    }
}

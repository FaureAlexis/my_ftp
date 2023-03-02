/*
** EPITECH PROJECT, 2023
** test logger
** File description:
** tests
*/

#include "../../include/logger.h"
#include "../tests.h"

Test(logger, test_logger_wrong_level, .init = redirect_all_std)
{
    cr_assert_eq(log_message(8, "test"), 84);
}

Test(logger, test_log_none_level, .init = redirect_all_std)
{
    cr_assert_eq(log_message(LOG_NONE, "test"), 0);
}

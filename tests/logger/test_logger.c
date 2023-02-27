/*
** EPITECH PROJECT, 2023
** test logger
** File description:
** tests
*/

#include <criterion/criterion.h>
#include "../../include/logger.h"

Test(logger, test_logger_success)
{
    cr_assert_eq(log_message(LOG_SUCCESS, "test"), 0);
}

Test(logger, test_logger_error)
{
    cr_assert_eq(log_message(LOG_ERROR, "test"), 0);
}

Test(logger, test_logger_warning)
{
    cr_assert_eq(log_message(LOG_WARNING, "test"), 0);
}

Test(logger, test_logger_info)
{
    cr_assert_eq(log_message(LOG_INFO, "test"), 0);
}

Test(logger, test_logger_debug)
{
    cr_assert_eq(log_message(LOG_DEBUG, "test"), 0);
}

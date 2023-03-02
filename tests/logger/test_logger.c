/*
** EPITECH PROJECT, 2023
** test logger
** File description:
** tests
*/

#include "../../include/logger.h"
#include "../tests.h"

Test(logger, test_logger_success, .init = redirect_all_std)
{
    cr_assert_eq(log_message(LOG_SUCCESS, "test"), 0);
}

Test(logger, test_logger_error, .init = redirect_all_std)
{
    cr_assert_eq(log_message(LOG_ERROR, "test"), 0);
}

Test(logger, test_logger_warning, .init = redirect_all_std)
{
    cr_assert_eq(log_message(LOG_WARNING, "test"), 0);
}

Test(logger, test_logger_info, .init = redirect_all_std)
{
    cr_assert_eq(log_message(LOG_INFO, "test"), 0);
}

Test(logger, test_logger_debug, .init = redirect_all_std)
{
    cr_assert_eq(log_message(LOG_DEBUG, "test"), 0);
}

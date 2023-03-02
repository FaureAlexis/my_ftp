/*
** EPITECH PROJECT, 2023
** logger
** File description:
** log functions
*/

#include "../../include/logger.h"

const char *level_colors[] = {"\033[0;0m", "\033[0;31m", "\033[0;33m",
    "\033[0;34m", "\033[0;32m", "\033[0;35m", "\033[0;32m"};

const char *level_names[] = {
    "NONE", "ERROR", "WARNING", "INFO", "SUCCESS", "DEBUG"};
int log_level = LOG_DEBUG;

static int print_time(void)
{
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%d/%m/%Y %H:%M:%S", tm_info);
    printf("%s - ", time_str);
    return 0;
}

static int print_level(enum LogLevel level)
{
    const char *level_str = "";
    const char *color = "";
    switch (level) {
        case LOG_ERROR:
        case LOG_WARNING:
        case LOG_INFO:
        case LOG_SUCCESS:
        case LOG_DEBUG:
            level_str = level_names[level];
            color = level_colors[level];
            break;
        case LOG_NONE: break;
    }
    printf("%s[%s] ", color, level_str);
    return 0;
}

static int print_message(const char *format, va_list args)
{
    vprintf(format, args);
    printf("%s\n", level_colors[LOG_NONE]);
    return 0;
}

int log_message(enum LogLevel level, const char *format, ...)
{
    if (level > log_level)
        return 84;
    print_level(level);
    print_time();
    va_list args;
    va_start(args, format);
    print_message(format, args);
    va_end(args);
    return 0;
}

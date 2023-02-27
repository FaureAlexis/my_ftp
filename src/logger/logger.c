/*
** EPITECH PROJECT, 2023
** logger
** File description:
** log functions
*/

#include "../../include/logger.h"

const char *level_colors[] = {"\033[0;0m", "\033[0;31m", "\033[0;33m",
    "\033[0;34m", "\033[0;32m", "\033[0;35m", "\033[0;32m"};

int log_level = LOG_DEBUG;

int log_message(enum LogLevel level, const char *format, ...)
{
    if (level > log_level)
        return 84;
    const char *level_str = "";
    const char *color = "";
    switch (level) {
        case LOG_ERROR:
            level_str = "ERROR";
            color = level_colors[LOG_ERROR];
            break;
        case LOG_WARNING:
            level_str = "WARNING";
            color = level_colors[LOG_WARNING];
            break;
        case LOG_INFO:
            level_str = "INFO";
            color = level_colors[LOG_INFO];
            break;
        case LOG_SUCCESS:
            level_str = "SUCCESS";
            color = level_colors[LOG_SUCCESS];
            break;
        case LOG_DEBUG:
            level_str = "DEBUG";
            color = level_colors[LOG_DEBUG];
            break;
        case LOG_NONE: break;
    }
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%d/%m/%Y %H:%M:%S", tm_info);

    va_list args;
    va_start(args, format);
    printf("%s[%s] %s - ", color, level_str, time_str);
    vprintf(format, args);
    printf("%s\n", level_colors[LOG_NONE]);
    va_end(args);
    return 0;
}

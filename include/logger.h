/*
** EPITECH PROJECT, 2023
** logger
** File description:
** logger
*/

#ifndef LOGGER_H
    #define LOGGER_H
    #include <stdarg.h>
    #include <stdio.h>
    #include <time.h>

enum LogLevel {
    LOG_NONE = 0,
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_SUCCESS,
    LOG_DEBUG,
};

int log_message(enum LogLevel level, const char *format, ...);
#endif /* !LOGGER_H */

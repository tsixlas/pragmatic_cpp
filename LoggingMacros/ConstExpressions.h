#pragma once

#define DEBUG_LEVEL 1
#define INFO_LEVEL 2
#define ERROR_LEVEL 3

#define LOG_DEBUG(MESSAGE)                              \
{                                                       \
    if (LogLevel <= DEBUG_LEVEL)                        \
        std::cout << "DEBUG: " << MESSAGE << std::endl; \
}                                                       \

#define LOG_INFO(MESSAGE)                               \
{                                                       \
    if (LogLevel <= INFO_LEVEL)                         \
        std::cout << "INFO: " << MESSAGE << std::endl;  \
}                                                       \

#define LOG_ERROR(MESSAGE)                              \
{                                                       \
    if (LogLevel <= ERROR_LEVEL)                        \
        std::cout << "ERROR: " << MESSAGE << std::endl; \
}                                                       \

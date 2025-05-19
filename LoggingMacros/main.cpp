#include <iostream>
#include "ConstExpressions.h"

#define LOG( MESSAGE )                                          \
{                                                               \
    std::cout << __FUNCTION__ << ": " << MESSAGE << std::endl;  \
}

int main() {
    // Simple loggin
    LOG("The cat sat on the mat")

    constexpr unsigned int LogLevel = INFO_LEVEL;
    LOG_DEBUG("A debug message")
    LOG_INFO("An info message")
    LOG_ERROR("An error message")
}

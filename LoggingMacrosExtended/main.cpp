#include <iostream>
#include "ConstExpressions.h"

constexpr unsigned int LogLevel = INFO_LEVEL;

int main() {
    LOG_DEBUG("A debug message")
    LOG_INFO("An info message")
    LOG_ERROR("An error message")
}

#include <iostream>

#define LOG(MESSAGE)                                            \
{                                                               \
    std::cout << __FUNCTION__ << ": " << MESSAGE << std::endl;  \
}

int main() {
    LOG("The cat sat on the mat")
}

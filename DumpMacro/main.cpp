#include <iostream>

#define DUMP(MESSAGE,...)                                                                   \
{                                                                                           \
    std::cout << "Function: " << __FUNCTION__ << " - " << MESSAGE << " " << __VA_ARGS__;    \
    std::cout << std::endl;                                                                 \
}                                                                                           \

int main(){
    DUMP( "I am here", 1)
    DUMP( "I am here", 2)
}

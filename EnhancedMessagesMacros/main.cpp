#include <iostream>

#pragma message("In file " __FILE__)

#define MESSAGE(msg)                            \
{                                               \
    std::cout << __FILE__ << msg << std::endl;  \
}                                               \

//    #pragma message(msg)                      \

int main(){
    MESSAGE(": Add code here");
}
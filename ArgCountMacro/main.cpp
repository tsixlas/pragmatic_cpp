#include <iostream>

#define ARG_COUNT( ... )                                    \
{                                                           \
    std::cout << sizeof((int[]){__VA_ARGS__})/sizeof(int);  \
    std::cout << std::endl;                                 \
}                                                           \

int main(){
    ARG_COUNT(1, 2, 3)
}

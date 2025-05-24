#include <iostream>

#define FIRST 1
#define SECOND FIRST

#define PRINT( INDEX, VALUE )                       \
    std::cout << "The value at index: " << INDEX << \
    " is " << VALUE << std::endl;                   \


int main(){
    int first = FIRST;
    std::cout << "Macro nested value: " << first << std::endl;
    int second = SECOND;
    std::cout << "Macro nested value: " << second << std::endl;
}

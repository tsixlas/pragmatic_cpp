#include <iostream>

#define FIRST 1
#define SECOND FIRST

#define PRINT( INDEX, VALUE )                       \
    std::cout << "The value at index: " << INDEX << \
    " is " << VALUE << std::endl;                   \

 #define LOOP_PRINT( COUNT )        \
 int value = START_VALUE;           \
 for( int i = 0; i < COUNT; i++ ){  \
 PRINT( i, value )                  \
 value += START_VALUE;              \
 }                                  \

#define START_VALUE 2

int main(){
    int first = FIRST;
    std::cout << "Macro nested value: " << first << std::endl;
    int second = SECOND;
    std::cout << "Macro nested value: " << second << std::endl;

    LOOP_PRINT(3)
}

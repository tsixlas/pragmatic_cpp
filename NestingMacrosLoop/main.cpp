#include <iostream>

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
    LOOP_PRINT(3)
}

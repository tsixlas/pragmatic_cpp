#include <iostream>

#define LINE_NUMBER( NUMBER )                                                                   \
{                                                                                               \
    std::cout << "Expected Line Number: " << NUMBER << " actual: " <<  __LINE__ << std::endl;   \
}                                                                                               \

int main(){
    LINE_NUMBER(1)
    LINE_NUMBER(2)
}

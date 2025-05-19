#include <iostream>

#define SUM_AND_DISPLAY(x,y)        \
    int sum = x + y;                \
    std::cout << sum << std::endl;  \

inline void SumAndDisplay(const int x, const int y){
    int sum = x + y;
    std::cout << sum << std::endl;
}


int main() {
    std::cout << "Macro sum: ";
    SUM_AND_DISPLAY(3, 5);

    std::cout << "Inline sum: ";
    SumAndDisplay(3,6);
}

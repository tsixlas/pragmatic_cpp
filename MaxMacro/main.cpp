#include <iostream>

#define MAX(a, b) a > b ? a : b;
#define MAX_INLINE(a, b)( a > b ? a : b )

#define MAX_EXPANDED(a, b)  \
({                          \
    auto ret = 0;           \
    if( a > b ) {           \
        ret = a;            \
    } else {                \
        ret = b;            \
    }                       \
    ret;                    \
})\


int main() {
    float value1 = 3.7;
    float value2 = 1.2;
    auto max_value = MAX(value1, value2)
    std::cout << "Max Value is " << max_value << std::endl;

    float result = MAX_INLINE(value1, value2) + 0.4;
    std::cout << "Result is " << result << std::endl;

    std::cout << "Max value is " << MAX_INLINE(3,2) << std::endl;

    std::cout << "Max value is " << MAX_EXPANDED(2,3) << std::endl;
}

#include <iostream>
#include <cstdarg>

inline float Average(const int num, ...) {
    float total = 0.0;
    auto count = num;
    va_list lst;
    va_start(lst, num);
    while (count > 0) {
        total += static_cast<float>(va_arg(lst, int));
        count--;
    }
    va_end(lst);
    float average = total / static_cast<float>(num);
    return average;
}

#define ARRAY_COUNT(...) \
    (sizeof((int[]){__VA_ARGS__})/sizeof(int))

#define AVERAGE( ... ) \
    Average(ARRAY_COUNT(__VA_ARGS__), __VA_ARGS__);


int main(){
    float av = AVERAGE(1,2,3,4,5,6);
    std::cout << "Average: " << av << std::endl;
}


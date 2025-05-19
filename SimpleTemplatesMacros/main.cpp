#include <iostream>
#include <vector>
#include <cstdarg>

template<typename T>
unsigned int arrayCount(std::initializer_list<T> &&list) {
    return list.size();
}

template<typename T>
inline float AverageT(const unsigned int num, ...) {
    float total = 0.0;
    auto count = num;
    va_list lst;
    va_start(lst, num);
    while (count > 0) {
        total += static_cast<float>(va_arg(lst, T));
        count--;
    }
    va_end(lst);
    float average = total / static_cast<float>(num);
    return average;
}

#define AVERAGET(T, ... )                                   \
    AverageT<T>(arrayCount<T>({__VA_ARGS__}), __VA_ARGS__); \

int main(){
    auto avg = AVERAGET(double, 1.2, 2.1, 3.3, 4.5, 5.2, 6.0);
    std::cout << "Template Average: " << avg << std::endl;
}

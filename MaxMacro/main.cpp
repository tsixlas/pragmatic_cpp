#include <iostream>

#define MAX(a, b) a > b ? a : b;

int main() {
    auto max_value = MAX(3,2)
    std::cout << "Max Value is " << max_value << std::endl;
}

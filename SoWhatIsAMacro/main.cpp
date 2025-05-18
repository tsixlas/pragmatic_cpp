#include <iostream>

#define PI 3.142

int main() {
    float radius = 0.0;
    std::cout << "Enter a radius" << std::endl;
    std::cin >> radius;
    float area = PI * radius * radius;
    float circumference = 2.0 * PI * radius;
    std::cout << "Circle area is: " << area << std::endl;
    std::cout << "Circle circumference is: " << circumference << std::endl;
}

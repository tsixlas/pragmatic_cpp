#include "e01_introduction.h"

void e01_introduction_instance() {
    float radius = 0.0;
    std::cout << "Enter a radius: " << std::endl;
    std::cin >> radius;
    float area = PI_MACRO * radius * radius;           // Using macro
    float circumference = 2.0 * PI_CONSTEXPR * radius; // Using constexpr
    std::cout << "Circle area is: " << area << std::endl;
    std::cout << "Circle circumference is: " << circumference << std::endl;
}

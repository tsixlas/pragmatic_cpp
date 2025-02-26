#include <iomanip>
#include <math.h>
#include <iostream>

// Example on how to create template function specialisations

class myClass{
public:
    myClass(){}

    // Define the generic / default implementation. As it is type T, it shoud be in the header file
    template <typename T>
    void foo(const T& t){
        std::cout << "Generic: " << t << std::endl;
    }
};

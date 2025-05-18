#include <iostream>

#define LOCAL_SCOPE()   \
{                       \
    int i = 3;          \
    i++;                \
}                       \

#define OUTSIDE_SCOPE() \
{                       \
    i = 3;              \
    i++;                \
}                       \

int main() {
    int i = 2;
    LOCAL_SCOPE()
    std::cout << "Local: " << i << std::endl;
    OUTSIDE_SCOPE()
    std::cout << "Outside: " << i << std::endl;

}

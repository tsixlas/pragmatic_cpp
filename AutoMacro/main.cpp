#include <iostream>

#define NON_AUTO( DEFAULT_VALUE )                   \
    int local = DEFAULT_VALUE;                      \
    std::cout << "Non auto: " << local << std::endl;\

#define AUTO( DEFAULT_VALUE )                           \
    auto auto_local = DEFAULT_VALUE;                    \
    std::cout << "Auto: " << auto_local << std::endl;   \

#define RETURN_NON_AUTO( DEFAULT_VALUE )    \
({                                          \
    int local = DEFAULT_VALUE;              \
    local;                                  \
})                                          \

#define RETURN_AUTO( DEFAULT_VALUE )    \
({                                      \
    auto local = DEFAULT_VALUE;         \
    local;                              \
})                                      \

int main() {
    NON_AUTO(3.142);
    AUTO(3.142);

    std::cout << "Return non-auto: " << RETURN_NON_AUTO(3.142) << std::endl;
    std::cout << "Return non-auto: " << RETURN_AUTO(3.142) << std::endl;

}

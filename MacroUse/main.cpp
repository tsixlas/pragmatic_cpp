#include <iostream>
#include <vector>

#define PRINT_LIST( CONTAINER ){                            \
    unsigned int count = 0;                                 \
    for( auto item: CONTAINER){                             \
        std::cout << count << " - " << item << std::endl;   \
        count++;                                            \
        }                                                   \
    }                                                       \

int main() {
    std::vector<int> lst = {10, 20, 30, 40};
    PRINT_LIST(lst)
}

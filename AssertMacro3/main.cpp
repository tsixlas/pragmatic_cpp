#include <iostream>

#define ASSERT_AND_THROW(condition)                     \
    if (!(condition)){                                  \
    throw std::runtime_error(#condition " is false");   \
    }                                                   \

namespace {
    void ProcessPointer(int *p) {
        ASSERT_AND_THROW(p != nullptr)
        //...
    }
}

int main(){
    ProcessPointer(nullptr);
}


#include <iostream>
#include <cassert>

#define ASSERT_AND_RETURN(condition, code)  \
{                                           \
    if (!(condition)) {                     \
        assert(false && #condition);        \
        return code;                        \
    }                                       \
}                                           \

namespace {
    int32_t ProcessPointer(int *p) {
        ASSERT_AND_RETURN(p != nullptr, -1)
        //...
        return 1;
    }
}

int main() {
    return ProcessPointer(nullptr);
}

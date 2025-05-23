#include <iostream>
#include <cassert>

namespace {
    void ProcessPointer(int *p) {
        assert(p != nullptr);
        //...
    }
}

int main(){
    ProcessPointer(nullptr);
}

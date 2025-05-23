#include <iostream>
#include <cassert>

namespace {
    void ProcessPointer(int *p){
        assert("Pointer is null" && p != nullptr);
        //...
    }
}

int main(){
    ProcessPointer(nullptr);
}

#include <iostream>
#define CREATE( NAME )              \
void My##NAME(){                    \
    std::cout << #NAME << std::endl;\
}

namespace {
    CREATE(Fred);
}

int main() {
    MyFred();
}

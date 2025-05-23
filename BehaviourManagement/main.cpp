#include <iostream>

enum class MyOS {
    eUSING_WINDOWS = 0,
    eUSING_LINUX,
    eUSING_MACOS,
    eUSING_UNIX
};

inline MyOS MyOSDetector() {
    MyOS os = MyOS::eUSING_WINDOWS;
#if defined(_WIN32) || defined(_WIN64) ||  defined(__WIN32__) || defined(__WINDOWS__)
    #define USING_WINDOWS
    os = MyOS::eUSING_WINDOWS;
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
    #define USING_LINUX
    os = MyOS::eUSING_LINUX;
#elif defined(__APPLE__) && defined(__MACH__)
    #define USING_MACOS
    os = MyOS::eUSING_MACOS;
#elif defined(__UNIX__)
    #define USING_UNIX
    os = MyOS::eUSING_UNIX;
#endif
    return os;
}

namespace {
    const MyOS os = MyOSDetector();
}

#define DETECT_OS MyOSDetector()

int main(){
    std::string myOSString;
    switch (os) {
        case MyOS::eUSING_WINDOWS: myOSString = "Windows"; break;
        case MyOS::eUSING_LINUX: myOSString = "Linux"; break;
        case MyOS::eUSING_MACOS: myOSString = "MacOS"; break;
        case MyOS::eUSING_UNIX: myOSString = "Unix"; break;
    }
    std::cout << "MY OS is " << myOSString << std::endl;
}

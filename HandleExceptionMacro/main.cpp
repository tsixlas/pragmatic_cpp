#include <iostream>
#include <exception>

#define HANDLE_EXCEPTION()                                  \
    catch( std::runtime_error & ex ){                       \
        std::cerr << ex.what() << std::endl;                \
    }                                                       \
    catch(...){                                             \
        std::cerr << "Unhandled exception" << std::endl;    \
    }                                                       \

#define LOG_EXCEPTION(exception)                                            \
    std::cerr << "Exception handled: " << std::string(__FUNCTION__)         \
    << " at line: " << __LINE__ <<  " - " << exception.what() << std::endl; \

int main() {
    try{
        throw std::runtime_error("Example error");
    }
    HANDLE_EXCEPTION()

    try {
        throw std::runtime_error("Another example error");
    } catch (std::runtime_error &ex) {
        LOG_EXCEPTION(ex)
    }

}

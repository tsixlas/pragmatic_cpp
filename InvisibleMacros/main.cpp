#include <iostream>
#include <exception>
#include <vector>
#include <memory>

class BaseException : public std::exception {
public:
    BaseException(const std::string &file, unsigned int line, const std::string &function, const std::string &message)
        : m_message(message + "\nFile:" + file + " Line: " + std::to_string(line) + " Function: " + function)
    {}

    [[nodiscard]] const char *what() const noexcept override {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

class BadMemoryAllocation : public BaseException {
public:
    BadMemoryAllocation(const std::string &file, unsigned int line, const std::string &function)
        : BaseException(file, line, function, "Memory Allocation failed")
    {}
};


class MyObject{
public:
    MyObject(){throw std::bad_alloc();}
};

int main(){
    std::shared_ptr<MyObject> p;
    try{
        p = std::make_shared<MyObject>();
    } catch ( std::bad_alloc &){
        throw BadMemoryAllocation( __FILE__, __LINE__, __FUNCTION__);
    } catch( std::exception &ex ){
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}

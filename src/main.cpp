#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <map>
#include <memory>

#include "../include/spec.h"

using namespace std;

typedef unsigned int UINT;

// ID //

// Can be defined  in its own file to be shared across files
using ID = uint16_t;

// Example class that shows the use of using
class Store{
public:
    float Get(ID id);
    void Set(ID id, float v);
private:
    using DataLookup = std::unordered_map<ID, float>;
    DataLookup m_data;
};

// Class pointers //

// Include a Ptr on your class
class MyClass{
public:
    using Ptr = std::shared_ptr<MyClass>;
};

// An example ugly definition
void UglyFoo(std::shared_ptr<MyClass> p);

// Using the Ptr definition you have an easier and simpler definition
void PrettyFoo(MyClass::Ptr p);

// Templates //
using Lookup = std::map<std::string, MyClass::Ptr>;

// Macros //
// The definition 
#define max(a, b) a > b ? a : b 

void usage_of_macros(){
    float value1 = 2.7;
    float value2 = 3.4;
    float result = max(value1, value2); 
    // The above line is the same as:
    float result1 = value1 > value2 ? value1 : value2; 

    // Correct final semicolon (not) use on the definition allows more natural use
    float result2 = max(value1, value2) + 0.4; 
}

#define FIELD(TYPE, NAME, initVal) \
public:                            \
    void Set##NAME(TYPE v){        \
        m_##NAME = v;              \
    }                              \
    TYPE Get##NAME(){              \
        return m_##NAME;           \
    };                             \
private:                           \
    TYPE m_##NAME{initVal}

//Seriously simplifies the definition of data classes
class DataClass{
    FIELD(int, One, 0);
    FIELD(float, Two, 0);
};

//enable_shared_from_this
// Great functionality when required but comes with a cost. Consider factory method to ensure smooth operation
class voiceRecorder: public enable_shared_from_this<voiceRecorder>{
    struct Private{explicit Private() = default;};
public:
    voiceRecorder(Private){} //Private constructor

    using Ptr = std::shared_ptr<voiceRecorder>;

    //Factory method ensures object is always wrapped around a shared pointer that the enable_shared_from_this requires
    static Ptr Create(){
        return std::make_shared<voiceRecorder>(Private());
    }
};



int main(){
    cout << "Hallo world" << endl;
    voiceRecorder::Ptr obj =  voiceRecorder::Create();

    // Demonstate 
    myClass c;

    std::cout << "Show some function specialization" << std::endl;
    int arg = 6;
    c.foo(arg);
    c.foo("test");
    c.foo(3.14f);
    c.foo(M_PI);
}
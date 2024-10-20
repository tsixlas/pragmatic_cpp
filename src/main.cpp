#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <map>
#include <memory>

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


int main(){
    cout << "Hallo world" << endl;
}
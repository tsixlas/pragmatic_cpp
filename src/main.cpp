#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <map>
#include <memory>

using namespace std;

typedef unsigned int UINT;

// ID //

// Can be defined  in it's own file to be shared across files
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

int main(void){
    cout << "Hallo world" << endl;
}
#include <spec.h>

// Specializations can be in the .cpp file and don't need explicit definition
template<>  void myClass::foo(const float& t){
    const auto default_precision{std::cout.precision()};
    std::cout << "Float:" << std::setprecision(8) << t << std::setprecision(default_precision) << std::endl;
}
template<>  void myClass::foo(const double& t){
    const auto default_precision{std::cout.precision()};
    std::cout << "Double:" << std::setprecision(12) << t << std::setprecision(default_precision) << std::endl;
}
template<>  void myClass::foo(const int& t){
    std::cout << "Integer: " << t << std::endl;
}

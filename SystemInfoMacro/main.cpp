#include <iostream>

#define Register(name, type)                   \
public:                                        \
type get_##name() const { return m_##name; };  \
void set_##name(type val) { m_##name = val; }; \
private:                                       \
type m_##name = 0                              \

class SystemInfoMacro{
    Register(temperatureCelcius, float);
    Register(CPUcoreCount, int);
    Register(CPUfreqGhz, float);
    Register(memoryBytes, int);
    Register(storageBytes, int);
};

class SystemInfoMacroEquivalent {
public:
    float get_temperatureCelcius() const { return m_temperatureCelcius; }
    void set_temperatureCelcius(const float val) { m_temperatureCelcius = val; }
    int get_CPUcoreCount() const { return m_CPUcoreCount; }
    void set_CPUcoreCount(const int val) { m_CPUcoreCount = val; }
    float get_CPUfreqGhz() const { return m_CPUfreqGhz; }
    void set_CPUfreqGhz(const float val) { m_CPUfreqGhz = val; }
    int get_memoryBytes() const { return m_memoryBytes; }
    void set_memoryBytes(const int val) { m_memoryBytes = val; }
    int get_storageBytes() const { return m_storageBytes; }
    void set_storageBytes(const int val) { m_storageBytes = val; }

private:
    float m_temperatureCelcius = 0;
    int m_CPUcoreCount = 0;
    float m_CPUfreqGhz = 0;
    int m_memoryBytes = 0;
    int m_storageBytes = 0;
};

int main() {
    SystemInfoMacro info;
    info.set_temperatureCelcius(10);
    info.set_CPUcoreCount(2);
    info.set_CPUfreqGhz(50);
    info.set_memoryBytes(100);
    info.set_storageBytes(1000);

    std::cout << "Temperature" << info.get_temperatureCelcius() << std::endl;
    std::cout << "CPU core count: " << info.get_CPUcoreCount() << std::endl;
    std::cout << "CPU frequency GHz: " << info.get_CPUfreqGhz() << std::endl;
    std::cout << "Memory Bytes: " << info.get_memoryBytes() << std::endl;
    std::cout << "Storage Bytes: " << info.get_storageBytes() << std::endl;
}

#include <iostream>
#include <any>
#include <unordered_map>

enum class dataTypes {
    temperatureCelcius = 0,
    CPUcoreCount = 1,
    CPUfreqGhz = 2,
    memoryBytes = 3,
    storageBytes = 4
};

class SystemInfoScalableMap {
public:
    SystemInfoScalableMap() {
        set<float>(dataTypes::temperatureCelcius, 0);
        set<int>(dataTypes::CPUcoreCount, 0);
        set<float>(dataTypes::CPUfreqGhz, 0);
        set<int>(dataTypes::memoryBytes, 0);
        set<int>(dataTypes::storageBytes, 0);
    }

    template<typename T>
    T get(dataTypes dataType) {
        return std::any_cast<T>(m_map[dataType]);
    }

    template<typename T>
    void set(dataTypes type, T value) {
        m_map[type] = value;
    }

private:
    std::unordered_map<dataTypes, std::any> m_map;
};

int main() {
    SystemInfoScalableMap info;
    info.set<float>(dataTypes::temperatureCelcius, 10);
    info.set<int>(dataTypes::CPUcoreCount, 2);
    info.set<float>(dataTypes::CPUfreqGhz, 50);
    info.set<int>(dataTypes::memoryBytes, 100);
    info.set<int>(dataTypes::storageBytes, 1000);

    std::cout << "Temperature" << info.get<float>(dataTypes::temperatureCelcius) << std::endl;
    std::cout << "CPU core count: " << info.get<int>(dataTypes::CPUcoreCount) << std::endl;
    std::cout << "CPU frequency GHz: " << info.get<float>(dataTypes::CPUfreqGhz) << std::endl;
    std::cout << "Memory Bytes: " << info.get<int>(dataTypes::memoryBytes) << std::endl;
    std::cout << "Storage Bytes: " << info.get<int>(dataTypes::storageBytes) << std::endl;
    return 0;
}

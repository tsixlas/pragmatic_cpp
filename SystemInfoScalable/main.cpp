#include <iostream>
#include <any>

enum class dataTypes {
    temperatureCelcius = 0,
    CPUcoreCount = 1,
    CPUfreqGhz = 2,
    memoryBytes = 3,
    storageBytes = 4
};

class SystemInfoScalable {
public:
    SystemInfoScalable() {
        set<float>(dataTypes::temperatureCelcius, 0);
        set<int>(dataTypes::CPUcoreCount, 0);
        set<float>(dataTypes::CPUfreqGhz, 0);
        set<int>(dataTypes::memoryBytes, 0);
        set<int>(dataTypes::storageBytes, 0);
    }

    template<typename T>
    T get(dataTypes dataType) {
        return std::any_cast<T>(data[static_cast<int>(dataType)]);
    }

    template<typename T>
    void set(dataTypes type, T value) {
        data[static_cast<int>(type)] = value;
    }

private:
    std::any data[5];
};

int main() {
    SystemInfoScalable info;
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

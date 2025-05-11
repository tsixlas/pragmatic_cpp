#include "system_info.h"
#include "system_info_scalable.h"
#include "system_info_scalable_map.h"
#include "system_info_macro.h"
#include "system_info_macro_expanded.h"


#include "e01_introduction.h"
int main(){
    //e01_introduction_instance();

    std::cout << std::endl << "Example using the SystemInfo class" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    SystemInfo systemInfo;
    systemInfo.set_temperatureCelcius(25.0);
    systemInfo.set_CPUcoreCount(8);
    systemInfo.set_CPUfreqGhz(3.5);
    systemInfo.set_memoryBytes(16 * 1024); // 16 kB
    systemInfo.set_storageBytes(512 * 1024); // 512 kB
    std::cout << "System Information:" << std::endl;
    std::cout << "Temperature:\t" << systemInfo.get_temperatureCelcius() << " °C" << std::endl;
    std::cout << "CPU Count:\t" << systemInfo.get_CPUcoreCount() << std::endl;
    std::cout << "CPU Frequency:\t" << systemInfo.get_CPUfreqGhz() << " GHz" << std::endl;
    std::cout << "Memory:\t\t" << systemInfo.get_memoryBytes() << " bytes" << std::endl;
    std::cout << "Storage:\t" << systemInfo.get_storageBytes() << " bytes" << std::endl;

    std::cout << std::endl << "Example using the SystemInfoScalable class" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    SystemInfoScalable systemInfoScalable;
    systemInfoScalable.set<float>(dataTypes::temperatureCelcius, 28.0);
    systemInfoScalable.set<int>(dataTypes::CPUcoreCount, 6);
    systemInfoScalable.set<float>(dataTypes::CPUfreqGhz, 3.3);
    systemInfoScalable.set<int>(dataTypes::memoryBytes, 32 * 1024); // 32 kB
    systemInfoScalable.set<int>(dataTypes::storageBytes, 128 * 1024); // 128 kB
    std::cout << "Temperature:\t" << systemInfoScalable.get<float>(dataTypes::temperatureCelcius) << " °C" << std::endl;
    std::cout << "CPU Count:\t" << systemInfoScalable.get<int>(dataTypes::CPUcoreCount) << std::endl;
    std::cout << "CPU Frequency:\t" << systemInfoScalable.get<float>(dataTypes::CPUfreqGhz) << " GHz" << std::endl;
    std::cout << "Memory:\t\t" << systemInfoScalable.get<int>(dataTypes::memoryBytes) << " bytes" << std::endl;
    std::cout << "Storage:\t" << systemInfoScalable.get<int>(dataTypes::storageBytes) << " bytes" << std::endl;

    std::cout << std::endl << "Example using the SystemInfoScalableMap class" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    SystemInfoScalableMap systemInfoScalableMap;
    systemInfoScalableMap.set<float>(dataTypes::temperatureCelcius, 25.0);
    systemInfoScalableMap.set<int>(dataTypes::CPUcoreCount, 4);
    systemInfoScalableMap.set<float>(dataTypes::CPUfreqGhz, 3.1);
    systemInfoScalableMap.set<int>(dataTypes::memoryBytes, 4 * 1024); // 4 kB
    systemInfoScalableMap.set<int>(dataTypes::storageBytes, 1 * 1024 * 1024); // 1 MB
    std::cout << "Temperature:\t" << systemInfoScalableMap.get<float>(dataTypes::temperatureCelcius) << " °C" << std::endl;
    std::cout << "CPU Count:\t" << systemInfoScalableMap.get<int>(dataTypes::CPUcoreCount) << std::endl;
    std::cout << "CPU Frequency:\t" << systemInfoScalableMap.get<float>(dataTypes::CPUfreqGhz) << " GHz" << std::endl;
    std::cout << "Memory:\t\t" << systemInfoScalableMap.get<int>(dataTypes::memoryBytes) << " bytes" << std::endl;
    std::cout << "Storage:\t" << systemInfoScalableMap.get<int>(dataTypes::storageBytes) << " bytes" << std::endl;

    std::cout << std::endl << "Example using the SystemInfoMacro class" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    SystemInfoMacro systemInfoMacro;
    systemInfoMacro.set_temperatureCelcius(19.0);
    systemInfoMacro.set_CPUcoreCount(12);
    systemInfoMacro.set_CPUfreqGhz(3.8);
    systemInfoMacro.set_memoryBytes(64 * 1024); // 64 kB
    systemInfoMacro.set_storageBytes(256 * 1024); // 256 kB
    std::cout << "Temperature:\t" << systemInfoMacro.get_temperatureCelcius() << " °C" << std::endl;
    std::cout << "CPU Count:\t" << systemInfoMacro.get_CPUcoreCount() << std::endl;
    std::cout << "CPU Frequency:\t" << systemInfoMacro.get_CPUfreqGhz() << " GHz" << std::endl;
    std::cout << "Memory:\t" << systemInfoMacro.get_memoryBytes() << " bytes" << std::endl;
    std::cout << "Storage:\t" << systemInfoMacro.get_storageBytes() << " bytes" << std::endl;

    std::cout << std::endl << "Example using the SystemInfoMacroExpanded class" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    SystemInfoMacroExpanded systemInfoMacroExpanded;
    systemInfoMacroExpanded.set_temperatureCelcius(25.0);
    systemInfoMacroExpanded.set_CPUcoreCount(8);
    systemInfoMacroExpanded.set_CPUfreqGhz(3.5);
    systemInfoMacroExpanded.set_memoryBytes(16 * 1024); // 16 kB
    std::cout << "Temperature: " << systemInfoMacroExpanded.get_temperatureCelcius() << " °C" << std::endl;
    std::cout << "CPU Core Count: " << systemInfoMacroExpanded.get_CPUcoreCount() << std::endl;
    std::cout << "CPU Frequency: " << systemInfoMacroExpanded.get_CPUfreqGhz() << " GHz" << std::endl;
    std::cout << "Memory: " << systemInfoMacroExpanded.get_memoryBytes() << " bytes" << std::endl;
}
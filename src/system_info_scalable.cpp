#include "system_info_scalable.h"

SystemInfoScalable::SystemInfoScalable() {
    set<float>(dataTypes::temperatureCelcius, 0);
    set<int>(dataTypes::CPUcoreCount, 0);
    set<float>(dataTypes::CPUfreqGhz, 0);
    set<int>(dataTypes::memoryBytes, 0);
    set<int>(dataTypes::storageBytes, 0);
}

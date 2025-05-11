#include "system_info.h"

float SystemInfo::get_temperatureCelcius() {
    return m_temperatureCelcius;
}

void SystemInfo::set_temperatureCelcius(int val) {
    m_temperatureCelcius = val;
}

int SystemInfo::get_CPUcoreCount() {
    return m_CPUcoreCount;
}

void SystemInfo::set_CPUcoreCount(int val) {
    m_CPUcoreCount = val;
}

float SystemInfo::get_CPUfreqGhz() {
    return m_CPUfreqGhz;
}

void SystemInfo::set_CPUfreqGhz(float val) {
    m_CPUfreqGhz = val;
}

int SystemInfo::get_memoryBytes() {
    return m_memoryBytes;
}

void SystemInfo::set_memoryBytes(int val) {
    m_memoryBytes = val;
}

int SystemInfo::get_storageBytes() {
    return m_storageBytes;
}

void SystemInfo::set_storageBytes(int val) {
    m_storageBytes = val;
}
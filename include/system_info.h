#pragma once

class SystemInfo{
public:
    float get_temperatureCelcius();
    void set_temperatureCelcius(int val);
    int get_CPUcoreCount();
    void set_CPUcoreCount(int val);
    float get_CPUfreqGhz();
    void set_CPUfreqGhz(float val);
    int get_memoryBytes();
    void set_memoryBytes(int val);
    int get_storageBytes();
    void set_storageBytes(int val);

private:
    float m_temperatureCelcius = 0;
    int m_CPUcoreCount = 0;
    float m_CPUfreqGhz = 0;
    int m_memoryBytes = 0;
    int m_storageBytes = 0;
};
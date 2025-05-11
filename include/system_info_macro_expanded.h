#pragma once

class SystemInfoMacroExpanded{
public:
    float get_temperatureCelcius() const { return m_temperatureCelcius; };
    void set_temperatureCelcius(float val) { m_temperatureCelcius = val; };
private:
    float m_temperatureCelcius = 0;

public:
    int get_CPUcoreCount() const { return m_CPUcoreCount; };
    void set_CPUcoreCount(int val) { m_CPUcoreCount = val; };
private:
    int m_CPUcoreCount = 0;

public:
    float get_CPUfreqGhz() const { return m_CPUfreqGhz; };
    void set_CPUfreqGhz(float val) { m_CPUfreqGhz = val; };
private:
    float m_CPUfreqGhz = 0;

public:
    int get_memoryBytes() const { return m_memoryBytes; };
    void set_memoryBytes(int val) { m_memoryBytes = val; };
    private: int m_memoryBytes = 0;

};

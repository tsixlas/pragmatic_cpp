#pragma once
#include "register.h"

class SystemInfoMacro{
    Register(temperatureCelcius, float);
    Register(CPUcoreCount, int);
    Register(CPUfreqGhz, float);
    Register(memoryBytes, int);
    Register(storageBytes, int);
};

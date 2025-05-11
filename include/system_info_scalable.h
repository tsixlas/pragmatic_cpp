#pragma once

#include <any>

#include "data_types.h"

class SystemInfoScalable{
public:
    SystemInfoScalable();

    template <typename T>
    T get(dataTypes dataType) {
        return std::any_cast<T>(data[static_cast<int>(dataType)]); 
    }
    
    template <typename T>
    void set(dataTypes type, T value) {
        data[int(type)] = value;
    }

private:
    std::any data[5];
};

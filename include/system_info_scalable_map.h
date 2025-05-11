#pragma once

#include <any>
#include <unordered_map>

#include "data_types.h"

class SystemInfoScalableMap{
public:
    SystemInfoScalableMap();

    template <typename T>
    T get(dataTypes dataType) {
        return std::any_cast<T>(m_map[dataType]);
    }

    template <typename T>
    void set(dataTypes type, T value) {
        m_map[type] = value;
    }

private:
    std::unordered_map<dataTypes, std::any> m_map;
};

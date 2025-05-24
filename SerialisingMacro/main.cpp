#include <iostream>
 #include <cstdint>
#include <cstring>

class Translator {
public:
    template<typename T>
    T Get() { return T(); }

    void Set(uint32_t value) {
        std::memcpy(m_buffer + m_position, &value, 4);
        m_position += 4;
    }

    void Set(const std::string &value) {
        uint32_t size = value.length();
        Set(size);
        for (auto i = 0; i < size; i++) {
            m_buffer[m_position + i] = value[i];
        }
        m_position += size;
    }

    void Reset() { m_position = 0; }

protected:
    uint32_t m_position{0};
    uint8_t m_buffer[512]{""};
};

template<>
uint32_t Translator::Get() {
    uint32_t local;
    std::memcpy(&local, m_buffer + m_position, 4);
    m_position += 4;
    return local;
}

template<>
std::string Translator::Get() {
    std::string str;
    uint32_t size = Get<uint32_t>();
    for (auto i = 0; i < size; i++) {
        str += static_cast<char>(m_buffer[m_position + i]);
    }
    m_position += size;
    return str;
}

int main() {
    Translator trans;
    trans.Set(123);
    trans.Set("My demo string");
    trans.Reset();
    std::cout << "Integer: " << trans.Get<uint32_t>() << std::endl;
    std::cout << "String: " << trans.Get<std::string>() << std::endl;
}

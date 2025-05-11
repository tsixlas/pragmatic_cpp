#pragma once
// Macro definition to register
#define Register(name, type)                       \
public:                                            \
    type get_##name() const { return m_##name; };  \
    void set_##name(type val) { m_##name = val; }; \
private:                                           \
    type m_##name = 0;
    

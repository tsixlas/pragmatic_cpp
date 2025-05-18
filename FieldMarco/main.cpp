#include <iostream>

#define FIELD( TYPE, NAME )             \
    public:                             \
        void Set##NAME( const TYPE v ){ \
            m_##NAME = v;               \
        }                               \
        TYPE const Get##NAME() {        \
            return m_##NAME;            \
        }                               \
    private:                            \
        TYPE m_##NAME{0}                \

class MyFieldClass {
    FIELD(int, One);
    FIELD(float, Two);
};

class MyFieldClassEquivalent {
public:
    void SetOne(const int v) { m_One = v; }
    int GetOne() const { return m_One; }
    void SetTwo(const float v) { m_Two = v; }
    float GetTwo() const { return m_Two; }

private:
    int m_One{0};
    float m_Two{0};
};

int main() {
    MyFieldClass myClass;
    myClass.SetOne(4);
    myClass.SetTwo(3.14);
    std::cout << "Field One of myClass is: " << myClass.GetOne() << std::endl;
    std::cout << "Field Two of myClass is: " << myClass.GetTwo() << std::endl;
}

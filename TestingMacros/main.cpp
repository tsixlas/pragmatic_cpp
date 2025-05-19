#include <iostream>

#define FIELD( TYPE, NAME )             \
    public:                             \
        void Set##NAME(const TYPE v){   \
            m_##NAME= v;                \
        }                               \
        TYPE Get##NAME() const{         \
            return m_##NAME;            \
        }                               \
     private:                           \
       TYPE m_##NAME=0;                 \

#define EXPECT_EQ(A, B)                                 \
    if(A!=B)                                            \
        std::cout << "Fields don't match" << std::endl; \
    else                                                \
        std::cout << "Test pass" << std::endl;          \


class MyFieldClass {
    FIELD(int, One);
public:
    void SetTwo(const int v){m_Two= v; }
    int GetTwo() const{ return m_Two; }
private: int m_Two=0;;
};

int main() {
    MyFieldClass fields;
    fields.SetOne(1);
    fields.SetTwo(1);
    EXPECT_EQ( fields.GetOne(), fields.GetTwo());

}

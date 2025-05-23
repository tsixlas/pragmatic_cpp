#include <iostream>
#include <vector>

#define FIELD(TYPE, NAME)               \
    public:                             \
        void Set##NAME(const TYPE v){   \
            m_##NAME = v;               \
        }                               \
        TYPE const Get##NAME() {        \
            return m_##NAME;            \
        }                               \
    private:                            \
        TYPE m_##NAME{0}                \

template<typename T>
class ParameterList {
public:
    void Add(T &value) { m_List.push_back(value); }

    T &Get(unsigned int pos) {
        if (pos >= m_List.size())
            throw std::runtime_error("Position is invalid");

        return m_List[pos];
    }

    unsigned int size() { return m_List.size(); }

private:
    using Parameters = std::vector<T>;
    Parameters m_List;
};

#define FIELD_LIST(TYPE, NAME)          \
     public:                            \
         void Add(TYPE & value){        \
             m_##NAME.Add(value);       \
         }                              \
         unsigned int Size##NAME(){     \
             return m_##NAME.size();    \
         }                              \
         TYPE & Get( unsigned int pos){ \
            return m_##NAME.Get(pos);   \
         }                              \
     private:                           \
         ParameterList<TYPE> m_##NAME;  \


class Person {
    FIELD(std::string, name);
    FIELD(std::string, email);
};

class Movie{
    FIELD( std::string, Title );
    FIELD( int32_t, ReleaseDate );
    FIELD( std::string, Director );
    FIELD_LIST( std::string, Actors );
};


int main() {
    Movie movie;
    movie.SetDirector("Stenstone");
    movie.SetReleaseDate(2025);
    movie.SetTitle("The Turkey");
    std::string actor = "Jules Brownstone";
    movie.Add(actor);
    actor = "Brice Runner";
    movie.Add(actor);

    std::cout << movie.GetTitle() << " (" << movie.GetReleaseDate() << ")" << std::endl;
    std::cout << "Directed by " << movie.GetDirector() << std::endl;
    std::cout << "Starring " << std::endl;
    for (unsigned int actorIter = 0; actorIter < movie.SizeActors(); actorIter++) {
        std::cout << "\t" << movie.Get(actorIter) << std::endl;
    }
}

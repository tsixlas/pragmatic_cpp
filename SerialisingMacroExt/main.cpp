#include <cstring>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

using Message = std::vector<uint8_t>;
using MessagePtr = std::shared_ptr<Message>;

template<typename T> class ITranslator{
public:
    virtual ~ITranslator() = default;

    virtual MessagePtr Serialize(T &value) = 0;
    virtual bool Deserialize(T &value, Message &msg) = 0;
};

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

public:
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
    m_position = m_position + size;
    return str;
}

template< typename OBJ >
class IGetterSetter{
public:
    using Ptr = std::shared_ptr<IGetterSetter>;
    virtual ~IGetterSetter() = default;
    virtual void Get(OBJ &obj, Translator & t) = 0;
    virtual void Set(OBJ &obj, Translator & t) = 0;
};

template< typename OBJ, typename T >
class GetterSetter: public IGetterSetter< OBJ>{
public:
    using SetterFunc = std::function<void (OBJ &obj, T &)>;
    using GetterFunc = std::function<void (OBJ &obj, T &)>;

    GetterSetter(SetterFunc set, GetterFunc get)
        : m_setter(std::move(set)), m_getter(std::move(get)) {}

    void Get(OBJ &obj, Translator &t) override {
        T value = t.Get<T>();
        m_setter(obj, value);
    }

    void Set(OBJ &obj, Translator &t) override {
        T value;
        m_getter(obj, value);
        t.Set(value);
    }
private:
    SetterFunc m_setter;
    GetterFunc m_getter;
};

template< typename T>
class GetSetTranslator: public ITranslator<T>{
public:
    using IGetterSetterPtr = std::shared_ptr<IGetterSetter<T>>;
    MessagePtr Serialize(T &value) override{
        m_translator.Reset();
        for( auto setter: m_GetterAndSetters){
            setter->Set(value, m_translator);
        }
        return std::make_shared<Message>(
            std::vector(m_translator.m_buffer, m_translator.m_buffer + m_translator.m_position));
    }
    bool Deserialize(T & value, Message & msg) override{
        try{
            std::copy(msg.begin(), msg.end(), m_translator.m_buffer);
            m_translator.Reset();
            for (const auto& getter: m_GetterAndSetters) {
                getter->Get(value, m_translator);
            }
        } catch (std::exception &ex) {
            return false;
        }
        return true;
    }

    void Add(const IGetterSetterPtr& gs) { m_GetterAndSetters.push_back(gs); }
private:
     Translator m_translator;
    using GetSetList = std::vector<IGetterSetterPtr>;
    GetSetList m_GetterAndSetters;
};

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

#define FIELD(TYPE, NAME)               \
    public:                             \
        void Set##NAME(const TYPE& v){  \
            m_##NAME = v;               \
        }                               \
        TYPE const Get##NAME() {        \
            return m_##NAME;            \
        }                               \
    private:                            \
        TYPE m_##NAME{0}                \

#define FIELD_LIST(TYPE, NAME)          \
     public:                            \
         void Add(TYPE & value){        \
             m_##NAME.Add(value);       \
         }                              \
         unsigned int Size##NAME(){     \
             return m_##NAME.size();    \
         }                              \
         TYPE & Get(unsigned int pos){  \
            return m_##NAME.Get(pos);   \
         }                              \
     private:                           \
         ParameterList<TYPE> m_##NAME;  \

class Movie{
    FIELD(std::string, Title);
    FIELD(int32_t, ReleaseDate);
    FIELD(std::string, Director);
    FIELD_LIST(std::string, Actors);
};

#define TRANSLATOR_GET_SET(OBJECT, TYPE, FIELD_NAME)                            \
{                                                                               \
    IGetterSetter<OBJECT>::Ptr p = std::make_shared<GetterSetter<OBJECT, TYPE>>(\
         [this](OBJECT &obj, TYPE & v){ obj.Set##FIELD_NAME(v);},               \
         [this](OBJECT &obj, TYPE & v){ v = obj.Get##FIELD_NAME();}             \
    );                                                                          \
    Add(p);                                                                     \
}                                                                               \

template< typename T>
class MovieTranslator : public GetSetTranslator<Movie> {
public:
    MovieTranslator() {
        TRANSLATOR_GET_SET(Movie, std::string, Title);
        TRANSLATOR_GET_SET(Movie, std::string, Director);
    }
};

int main() {
    Movie myMovie;
    myMovie.SetDirector("My phantasy director");
    myMovie.SetTitle("My phantasy title");
    std::cout << "Director: " << myMovie.GetDirector() << std::endl;
    std::cout << "Title: " << myMovie.GetTitle() << std::endl;

    MovieTranslator<Movie> myTranslator;
    MessagePtr myMessage = myTranslator.Serialize(myMovie);
    std::cout << "String representation: " << std::string(myMessage->begin(), myMessage->end()) << std::endl;

    // myMessage is sent and received through TCP/IP

    MovieTranslator<Movie> myReceiverTranslator;
    Movie myReceivedMovie;
    myReceiverTranslator.Deserialize(myReceivedMovie, *myMessage);
    std::cout << "Director: " << myReceivedMovie.GetDirector() << std::endl;
    std::cout << "Title: " << myReceivedMovie.GetTitle() << std::endl;
}
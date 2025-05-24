#include <cstring>
#include <functional>
#include <memory>
#include <vector>

using Message = std::vector<uint8_t>;
using MessagePtr = std::shared_ptr<Message>;

template< typename T > class ITranslator{
public:
    virtual MessagePtr Serialize( T &value ) = 0;
    virtual bool Deserialize( T & value, Message & msg ) = 0;
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

protected:
    uint32_t m_position{0};
    uint8_t m_buffer[512]{""};
};

template< typename OBJ >
class IGetterSetter{
public:
    using Ptr = std::shared_ptr<IGetterSetter>;
    ~IGetterSetter() = default;
    virtual void Get(OBJ &obj, Translator & t) = 0;
    virtual void Set(OBJ &obj, Translator & t) = 0;
};

template< typename OBJ, typename T >
class GetterSetter: public IGetterSetter< OBJ>{
public:
    using SetterFunc = std::function<void (OBJ & obj, T &)>;
    using GetterFunc = std::function<void (OBJ & obj, T & )>;
    GetterSetter( SetterFunc set, GetterFunc get ):m_setter(set),m_getter(get){}
    void Get(OBJ &obj, Translator & t) override {
        T value = t.Get<T>();
        m_setter( obj, value );
    }
    void Set(OBJ &obj, Translator & t) override {
        T value;
        m_getter( obj, value );
        t.Set(value);
    }
private:
    SetterFunc m_setter;
    GetterFunc m_getter;
};

template< typename T>
class GetSetTranslator: public ITranslator< T >{
public:
    using IGetterSetterPtr = std::shared_ptr<IGetterSetter< T > >;
    MessagePtr Serialize( T &value ) override{
        m_translator.Reset();
        for( auto setter: m_GetterAndSetters){
            setter->Set( value, m_translator);
        }
        return m_translator.Access();
    }
    bool Deserialize( T & value, Message & msg ) override{
        try{
            m_translator.Reset(msg);
            for( auto getter: m_GetterAndSetters){
                getter->Get( value, m_translator);
            }
        } catch ( std::exception & ex ){
            return false;
        }
        return true;
    }
    void Add( IGetterSetterPtr gs ){ m_GetterAndSetters.push_back( gs );}
private:
    Translator m_translator;
    using GetSetList = std::vector<IGetterSetterPtr>;
    GetSetList m_GetterAndSetters;
};


int main(){}
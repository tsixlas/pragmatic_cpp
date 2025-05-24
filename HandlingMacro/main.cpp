#include <atomic>
#include <deque>
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <unordered_map>

template<class T>
class WaitQueueTask {
public:
    using TPtr = std::shared_ptr<T>;

    WaitQueueTask() {
        m_queueThread = std::thread(&WaitQueueTask::Process, this);
    }

    virtual ~WaitQueueTask() {
        purge();
        Stop();
    }

    void Enqueue(TPtr &v) {
        std::unique_lock l(m_mutex);
        m_buffer.push_back(v);
        m_hasData.notify_one();
    }

    void Process() {
        Queue copyQueue;
        while (!m_stopRunning) {
            std::unique_lock l(m_mutex);
            m_hasData.wait(l, [this] { return HasData(); }); {
                copyQueue = m_buffer;
                m_buffer.clear();
                for (auto item: copyQueue) {
                    Handle(*item);
                }
            }
        }
    }

    void Stop() {
        m_stopRunning = true;
        auto stop_obj = std::make_shared<T>();
        Enqueue(stop_obj);
        if (m_queueThread.joinable()) { m_queueThread.join(); }
    }

protected:
    virtual void Handle(T &v) {
    }

    void purge() { m_buffer.clear(); }
    bool HasData() { return m_buffer.size(); }

private:
    using Queue = std::deque<TPtr>;
    Queue m_buffer;
    std::atomic<bool> m_stopRunning = {false};
    std::thread m_queueThread;
    std::condition_variable m_hasData;
    std::mutex m_mutex;
};

template< class Object >
class CallbackFunctor{
public:
    using Ptr = std::shared_ptr<CallbackFunctor<Object>>;
    virtual void operator()( Object & obj) = 0;
};

template< class Concrete, class Object >
class ConcreteCallbackFunctor: public CallbackFunctor<Object>{
public:
    using Callback = std::function< void ( Concrete & )>;
    ConcreteCallbackFunctor( Callback handler ):m_Handler(handler){}
    void operator()(Object & obj ){
        try{
            Concrete & c = dynamic_cast<Concrete & >( obj );
            m_Handler( c );
        }catch(... ){
        }
    }
private:
    Callback m_Handler;
};

template<class T, typename Type>
class QueuedObjectHandler : public WaitQueueTask<T> {
protected:
    using Callback = std::function<void (T &)>;

    void Handle(T &v) override {
        auto it = m_handlers.find(v.Type());
        if (it != m_handlers.end()) {
            m_handlers[v.Type()]->operator()(v);
        }
    }

    void Add(Type index, CallbackFunctor<T>::Ptr c) { m_handlers[index] = c; }

private:
    using Handlers = std::unordered_map<Type, typename CallbackFunctor<T>::Ptr>;
    Handlers m_handlers;
};

class BaseException : public std::exception {
public:
    BaseException(const std::string &file, unsigned int line, const std::string &function, const std::string &message)
        : m_message(message + "\nFile:" + file + " Line: " + std::to_string(line) + " Function: " + function)
    {}

    const char *what() const noexcept override {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

class BadMemoryAllocation : public BaseException {
public:
    BadMemoryAllocation(const std::string &file, unsigned int line, const std::string &function)
        : BaseException(file, line, function, "Memory Allocation failed")
    {}
};

#define ADD_HANDLER( PARENT, CHILD, HANDLER )                                           \
{                                                                                       \
    try{                                                                                \
        CHILD c;                                                                        \
            CallbackFunctor<Object>::Ptr p( new ConcreteCallbackFunctor<CHILD,PARENT>   \
            ( [this](CHILD & obj ){HANDLER(obj);}));                                    \
            Add( c.Type(), p );                                                         \
    }catch( std::bad_alloc & ) {                                                        \
        BadMemoryAllocation( __FILE__, __LINE__, __FUNCTION__ );                        \
    }                                                                                   \
}                                                                                       \

class Object{
public:
    using Ptr = std::shared_ptr<Object>;
    Object()= default;
    virtual ~Object() = default;
    virtual uint32_t Type() {return 0;}
};

class MyObjectOne: public Object{
public:
    MyObjectOne()= default;
    uint32_t Type() override {return 1;}
};
class MyObjectTwo: public Object{
public:
    MyObjectTwo()= default;
    uint32_t Type() override {return 2;}
};
class MyObjectThree: public Object{
public:
    MyObjectThree()= default;
    uint32_t Type() override {return 3;}
};

class MyDataQueue : public QueuedObjectHandler<Object, uint32_t> {
public:
    MyDataQueue() {
        ADD_HANDLER(Object, MyObjectOne, Handle)
        ADD_HANDLER(Object, MyObjectTwo, Handle)
        ADD_HANDLER(Object, MyObjectThree, Handle)
    }

    uint32_t CountOne() { return m_countOne; }
    uint32_t CountTwo() { return m_countTwo; }
    uint32_t CountThree() { return m_countThree; }

protected:
    void Handle(MyObjectOne &obj) { m_countOne++; }
    void Handle(MyObjectTwo &obj) { m_countTwo++; }
    void Handle(MyObjectThree &obj) { m_countThree++; }

private:
    uint32_t m_countOne{0};
    uint32_t m_countTwo{0};
    uint32_t m_countThree{0};
};



int main(){
    MyDataQueue queue;
    for( int i = 0; i< 3;i++){
        Object::Ptr obj = std::make_shared<MyObjectOne>();
        queue.Enqueue(obj);
        obj = std::make_shared<MyObjectTwo>();
        queue.Enqueue(obj);
        obj = std::make_shared<MyObjectThree>();
        queue.Enqueue(obj);
    }
    queue.Stop();
    std::cout << "Handled one: " << queue.CountOne() << std::endl;
    std::cout << "Handled two: " << queue.CountTwo() << std::endl;
    std::cout << "Handled three: " << queue.CountThree() << std::endl;
}


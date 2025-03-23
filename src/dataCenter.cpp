#include <iostream>
#include <queue>
#include <functional>

#include <dataCenter.h>
#include "messages.pb.h"

// In order to serialise / deserialise, it is assumed the undrelying send / receive
// also keeps the information on what the string is. That means you end up with a set
// of key - value pairs, where the key can be an enum and the value is a string
enum class MessageType{
    Person = 1,
    SearchRequest = 2,
    Movie = 3
};

void SerializeProto(){    
    // As receiving data is async, it is a good idea to not process the messages directy
    // but store them into a queue to be processed in a seperate thread
    std::queue<std::pair<MessageType, std::string>> receivingQueue;
    std::mutex m_queueMutex;

    // Simulating the receiving thread. The protos here are used to help build the string
    // representation that should happen on the sender abstracting the send /receive process
    {
        tutorial::Person person;
        person.set_name("Donald Duck");
        person.set_email("somewhere@nowhere.co.uk");
        std::lock_guard lock(m_queueMutex);
        receivingQueue.emplace(MessageType::Person, person.SerializeAsString());
    }


    // Simulating the processing thread (single data type, not dealing with the rest for now)
    {
        tutorial::Person receivedPerson;
        std::lock_guard lock(m_queueMutex);
        receivedPerson.ParseFromString(receivingQueue.front().second);
        cout << "Receiving:" << endl;
        cout << receivedPerson.DebugString() << endl;
    }

    // Lets add more elements to the list
    {
        tutorial::Movie movie;
        movie.set_title("The rock");
        movie.set_release_date(1996);
        movie.set_director("Michael Bay");
        movie.mutable_star()->Add("Sean Connery");
        movie.mutable_star()->Add("Nicolas Cage");
        std::lock_guard lock(m_queueMutex);
        receivingQueue.emplace(MessageType::Movie, movie.SerializeAsString());
    }

    // Let's receive the message the same way to help identify the pattern
    {
        tutorial::Movie receivedMovie;
        std::lock_guard lock(m_queueMutex);
        receivedMovie.ParseFromString(receivingQueue.back().second);
        cout << "Receiving:" << endl;
        cout << receivedMovie.DebugString() << endl;
    }

    // Let's try now to combine the above examples in a single loop
    {
        std::lock_guard lock(m_queueMutex);
        while (!receivingQueue.empty()) {
            tutorial::Movie receivedMovie;
            tutorial::Person receivedPerson;

            switch (receivingQueue.front().first) {
            case MessageType::Movie:
                receivedMovie.ParseFromString(receivingQueue.front().second);
                cout << "Receiving movie:" << endl;
                cout << receivedMovie.DebugString() << endl;
                break;
            case MessageType::Person:
                receivedPerson.ParseFromString(receivingQueue.front().second);
                cout << "Receiving person:" << endl;
                cout << receivedPerson.DebugString() << endl;
                break;
            }
            receivingQueue.pop();
        }
    }

    SerializeProto2();
}
/////////////////////////queue fill code/////////////////////////
void fillQueue(std::queue<std::pair<MessageType, std::string>>& receivingQueue, std::mutex& m_queueMutex){
    {
        tutorial::Person person;
        person.set_name("Donald Duck");
        person.set_email("somewhere@nowhere.co.uk");
        std::lock_guard lock(m_queueMutex);
        receivingQueue.emplace(MessageType::Person, person.SerializeAsString());
    }
    {
        tutorial::Movie movie;
        movie.set_title("The rock");
        movie.set_release_date(1996);
        movie.set_director("Michael Bay");
        movie.mutable_star()->Add("Sean Connery");
        movie.mutable_star()->Add("Nicolas Cage");
        std::lock_guard lock(m_queueMutex);
        receivingQueue.emplace(MessageType::Movie, movie.SerializeAsString());
    }
}
/////////////////////////queue fill code/////////////////////////

// At this point you realise that this is not scalable. Maintaining code like that
// can be really hard and error prone. It requires extensive testing to make sure the code
// behaves appropriately for each element of the list. In the example above the action is
// just to print to the screen but what will happen when instead of 2, we have 42 data types?

// This is where templates and macros may actually be really really helpful to make the code
// scalable, maintainable and simpler.

// To do so, we need 2 steps:
//   - isolate the parsing of each element of the list
//   - get rid of the switch statement as it's not maintainable

template <typename T>
class IData{
public:
    IData(std::string msg){
        T protoMsg;
        protoMsg.ParseFromString(msg);
        cout << "Receiving item:" << endl;
        cout << protoMsg.DebugString() << endl;
    }
};

void SerializeProto2(){
    std::queue<std::pair<MessageType, std::string>> receivingQueue;
    std::mutex m_queueMutex;
    fillQueue(receivingQueue, m_queueMutex);

    // Now we can rewrite the parsing of the list, using the template we created
    {
        std::lock_guard lock(m_queueMutex);
        while (!receivingQueue.empty()) {
            switch (receivingQueue.front().first) {
            case MessageType::Movie:
                IData<tutorial::Movie>(receivingQueue.front().second);
                break;
            case MessageType::Person:
                IData<tutorial::Person>(receivingQueue.front().second);
                break;
            }
            receivingQueue.pop();
        }
    }
    SerializeProto3();
}

// Ok this is slightly better but still suffers from the follwing issues:
// - The switch is still there. Apart from ugly (imaging the 42 entries) it's also slow
// - There is no obvious way to define and control what to do with the data (not only 
// print to the screen which is conveniently available on all messages)

// To do that we'll need to introduce specialised data classes to wrap around the proto messages
// That can look like this:
template <typename T>
class BaseData{
public:
    BaseData(std::string msg){
        m_msg.ParseFromString(msg);
    }
    virtual void processData() = 0;
protected:
    T m_msg;
};

// Data classes can customise to the data they are handling
class PersonHandler: public BaseData<tutorial::Person>{
public:
    PersonHandler(std::string msg): BaseData(msg){}

    void processData() override{
        cout << "Received person" << endl;
        cout << "Name: " << m_msg.name() << endl;
        cout << "email: " << m_msg.email() << endl;
        cout << endl;
    }
};

class MovieHandler: public BaseData<tutorial::Movie>{
public:
    MovieHandler(std::string msg): BaseData(msg){}

    void processData() override{
        cout << "Received movie" << endl;
        cout << "Title: " << m_msg.title() << endl;
        cout << "Release date: " << m_msg.release_date() << endl;
        cout << "Director: " << m_msg.director() << endl;
        cout << "Starring:" << endl;
        for(auto item:m_msg.star()){
            cout << "\t" << item << endl;
        }
        cout << endl;
    }
};

// Let's also create a template function to convert a class definition to a function and prepare
// to get rid of the switch but it needs to stay a little bit longer to become obvious
template <typename T>
void parseMessage(std::string msg){
    T hander(msg);
    hander.processData();
}

void SerializeProto3(){
    std::queue<std::pair<MessageType, std::string>> receivingQueue;
    std::mutex m_queueMutex;
    fillQueue(receivingQueue, m_queueMutex);

    // Let's now use our data classes and the template function
    {
        std::lock_guard lock(m_queueMutex);
        while (!receivingQueue.empty()) {
            switch (receivingQueue.front().first) {
            case MessageType::Movie:
                parseMessage<MovieHandler>(receivingQueue.front().second);
                break;
            case MessageType::Person:
                parseMessage<PersonHandler>(receivingQueue.front().second);
                break;
            }
            receivingQueue.pop();
        }
    }


    SerializeProto4();
}

void SerializeProto4(){
    std::queue<std::pair<MessageType, std::string>> receivingQueue;
    std::mutex m_queueMutex;
    fillQueue(receivingQueue, m_queueMutex);

   // Now let's fix the switch statement with the use of a map
   std::unordered_map<MessageType, std::function<void(std::string)>> map;
   map[MessageType::Movie] = parseMessage<MovieHandler>;
   map[MessageType::Person] = parseMessage<PersonHandler>;

   // And use the map to flush the queue
   {
        std::lock_guard lock(m_queueMutex);
        while (!receivingQueue.empty()) {
            map[receivingQueue.front().first](receivingQueue.front().second);
            receivingQueue.pop();
        }
    }
    SerializeProto5();
}

//Let's now try to tidy up (hide) the unnecesary complexity

// Some macros may help abstract the map complexity
#define REGISTER(dataType, dataHandler) map[dataType] = parseMessage<dataHandler>
#define CALLHANDLER(dataType, str) map[dataType](str)

void SerializeProto5(){
    std::queue<std::pair<MessageType, std::string>> receivingQueue;
    std::mutex m_queueMutex;
    fillQueue(receivingQueue, m_queueMutex);

    std::unordered_map<MessageType, std::function<void(std::string)>> map;
    REGISTER(MessageType::Movie, MovieHandler);
    REGISTER(MessageType::Person, PersonHandler);
    // <------------- Only place you need to register new message types
    //                Obviously you need to impelement the new handler

    // The code to flush the queue does not depend on the message types
    {
        std::lock_guard lock(m_queueMutex);
        while (!receivingQueue.empty()) {
            auto type = receivingQueue.front().first;
            auto data = receivingQueue.front().second;
            CALLHANDLER(type, data);
            receivingQueue.pop();
        }
    }
}
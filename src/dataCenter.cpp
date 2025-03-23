#include <iostream>
#include <queue>

#include <dataCenter.h>
#include "messages.pb.h"


void SerializeProto(){
    // In order to serialise / deserialise, it is assumed the undrelying send / receive
    // also keeps the information on what the string is. That means you end up with a set
    // of key - value pairs, where the key can be an enum and the value is a string
    enum class MessageType{
        Person = 1,
        SearchRequest = 2,
        Movie = 3
    };
    
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

    // At this point you realise that this is not scalable. Maintaining code like that
    // can be really hard and error prone. It requires extensive testing to make sure the code
    // behaves appropriately for each element of the list. In the example above the action is
    // just to print to the screen but what will happen when instead of 2, we have 42 data types?

    // This is where templates and macros may actually be really really helpful to make the code
    // scalable, maintainable and simpler.

    // To do so, we need 2 steps:
    //   - isolate the parsing of each element of the list
    //   - get rid of the switch statement as it's not maintainable
    
}
#include <dataCenter.h>
#include <iostream>
#include "messages.pb.h"

void SerializeProto(){
    //Transmit a person
    std::string sendString;
    {
        tutorial::Person person;
        person.set_name("Donald Duck");
        person.set_email("somewhere@nowhere.co.uk");
        sendString = person.SerializeAsString();
        cout << "Sending:" << endl;
        cout << person.DebugString() << endl;
    }

    //Receive
    std::string receiveString = sendString;
    {
        tutorial::Person receivedPerson;
        receivedPerson.ParseFromString(receiveString);
        cout << "Receiving:" << endl;
        cout << receivedPerson.DebugString() << endl;
    }
    
}
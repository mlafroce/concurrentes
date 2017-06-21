#include "Message.h"
#include "../Utils.h"
#include "../Log.h"

#define CRLF "\r\n"


//Serialized Message
//  "<<from>>CRLF<<to>>CRLF<<body>>"
//      body can contains CRLF's

Message::Message() : message("") {}

Message::Message(const char *serialized) :  message("") {
    parseSerialized((char*)serialized, &message);
}

Message::Message(std::string msg) : message(msg) {}

void Message::parseSerialized(char *c_serialized, std::string *message) {
    std::string serialized = c_serialized;
    *message = serialized;
}


const char* Message::serialize() {
    return this->message.c_str();
}

int Message::size() {
    return (int)std::string(this->serialize()).size();
}


std::string Message::getMessage() {
    return this->message;
}

void Message::setMessage(std::string msg) {
    this->message = msg;
}

#include "Message.h"
#include "../Utils.h"
#include "../Log.h"

#define CRLF "\r\n"


//Serialized Message
//  "<<from>>CRLF<<to>>CRLF<<body>>"
//      body can contains CRLF's

Message::Message() : from_id(0), to_id(0), message("") {}

Message::Message(const char *serialized) : from_id(0), to_id(0), message("") {
    parseSerialized((char*)serialized, &from_id, &to_id, &message);
}

Message::Message(int fromId, int toId, std::string msg) : from_id(fromId), to_id(toId), message(msg) {}

void Message::parseSerialized(char *c_serialized, int *from, int *to, std::string *message) {
    std::string serialized = c_serialized;
    std::vector<std::string> parts = Utils::splitString(serialized,CRLF);
    if (parts.size() < 3) {
        LOG_WARNING("Error al parsear message serializado, se esperan 3 componentes como minimo, hay " + std::to_string(parts.size()));
        return;
    }
    *from = atoi(parts[0].c_str());
    *to = atoi(parts[1].c_str());

    std::string partialMessage = "";
    for (int i = 2; i < parts.size(); i++) {
        partialMessage += parts[i] + (i == (parts.size()-1) ? "": CRLF);
    }
    if (serialized.substr( serialized.size() - 2 ) == CRLF) {
        partialMessage += CRLF;
    }

    *message = partialMessage;
}


const char* Message::serialize() {
    std::string serialize = std::to_string(this->from_id) + CRLF + std::to_string(this->to_id) + CRLF + this->message;
    return serialize.c_str();
}

int Message::size() {
    return (int)std::string(this->serialize()).size();
}

void Message::setReceptor(int id) {
    this->to_id = id;
}

int Message::getReceptor() {
    return to_id;
}

std::string Message::getMessage() {
    return this->message;
}

void Message::setMessage(std::string msg) {
    this->message = msg;
}

int Message::getTransmitter() {
    return from_id;
}

void Message::setTransmitter(int id) {
    this->from_id = id;
}
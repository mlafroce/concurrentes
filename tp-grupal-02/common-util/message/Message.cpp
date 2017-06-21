#include "Message.h"
#include "../Utils.h"
#include "../Log.h"

#define CRLF "\r\n"


//Serialized Message
//  "<<from>>CRLF<<to>>CRLF<<body>>"
//      body can contains CRLF's

Message::Message() : message_id(0), message("") {}

Message::Message(const char *serialized) : message_id(0), message("") {
    parseSerialized((char*)serialized, &message_id, &message);
}

Message::Message(int id, std::string msg) : message_id(id), message(msg) {}

void Message::parseSerialized(char *c_serialized, int *id, std::string *message) {
    std::string serialized = c_serialized;
    std::vector<std::string> parts = Utils::splitString(serialized,CRLF);
    if (parts.size() < 2) {
        LOG_WARNING("Error al parsear message serializado, se esperan 2 componentes como minimo, hay " + std::to_string(parts.size()));
        return;
    }
    *id = atoi(parts[0].c_str());

    std::string partialMessage = "";
    for (int i = 1; i < parts.size(); i++) {
        partialMessage += parts[i] + (i == (parts.size()-1) ? "": CRLF);
    }
    if (serialized.substr( serialized.size() - 2 ) == CRLF) {
        partialMessage += CRLF;
    }

    *message = partialMessage;
}


const char* Message::serialize() {
    std::string serialize = std::to_string(this->message_id) + CRLF + this->message;
    return serialize.c_str();
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

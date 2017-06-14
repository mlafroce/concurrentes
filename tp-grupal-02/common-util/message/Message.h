//
// Created by tomi on 14/06/17.
//

#ifndef CONCURRENTES_MESSAGE_H
#define CONCURRENTES_MESSAGE_H

#include "string"

class Message {
private:
    int from_id, to_id;
    std::string message;

    void parseSerialized(char* serialized, int* from, int* to, std::string *message);

private:
    Message(const char* serialize);
    Message();
    Message(int fromId, int toId,std::string message);

    const char* serialize();
    int size();

    int getTransmitter();
    void setTransmitter(int id);

    int getReceptor();
    void setReceptor(int id);

    std::string getMessage();
    void setMessage(std::string msg);
};


#endif //CONCURRENTES_MESSAGE_H

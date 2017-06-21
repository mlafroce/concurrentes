#ifndef CONCURRENTES_MESSAGE_H
#define CONCURRENTES_MESSAGE_H

#include "string"

class Message {
private:
    int message_id;
    std::string message;

    void parseSerialized(char* serialized, int* id, std::string *message);

public:
    Message(const char* serialize);
    Message();
    Message(int id, std::string message);

    const char* serialize();
    int size();

    int getId(){ return message_id; };
    void setId(int id){ message_id = id; };

    std::string getMessage();
    void setMessage(std::string msg);
};

#endif //CONCURRENTES_MESSAGE_H

#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H
#include <sys/ipc.h>

class MessageQueueBase {
public:
    /**
     * Joins an existing message queue,  or creates a new one if create == true
     */
    MessageQueueBase(key_t key);
    /**
     * Frees IPC
     */
    void destroyMessageQueue();
    /**
     * Sends buf content
     */
    void sendMessage(const void* buf, int bufSize, int msgType);
    /**
     * Receives message
     */
    void recvMessage(void* buf, int bufSize, int msgType);
    /**
     * Turns off ipc free
     */
    void preventDestroy();
private:
    int msgId;
};

class MessageQueue {
public:
    MessageQueue();
};

#endif // MESSAGEQUEUE_H

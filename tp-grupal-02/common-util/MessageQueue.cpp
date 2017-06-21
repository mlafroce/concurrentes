#include "MessageQueue.h"
#include "IpcException.h"
#include "Utils.h"
#include <cerrno>
#include <cstring>
#include <sys/msg.h>

MessageQueueBase::MessageQueueBase(key_t key) {
    this->msgId = msgget(key, IPC_CREAT | 0660 );
    if (this->msgId == -1 ) {
        throw IpcException(errno);
    }
}

MessageQueueBase::MessageQueueBase(const std::string& file, const char letter) {
    key_t key = Utils::generateKey(file,letter);
    this->msgId = msgget(key, IPC_CREAT | 0660 );
    if (this->msgId == -1 ) {
        throw IpcException(errno);
    }
}

void MessageQueueBase::sendMessage(const void* buf, int bufSize, int msgType) {
    struct msgbuf* msg = (struct msgbuf*)malloc(sizeof(struct msgbuf) + bufSize);
    msg->mtype = msgType;
    memcpy(msg->mtext, buf, bufSize);
    int status = msgsnd(this->msgId, msg, bufSize, 0);
    free(msg);
    if (status  == -1) {
        throw IpcException(errno);
    }
}

void MessageQueueBase::recvMessage(void* buf, int bufSize, int msgType) {
    struct msgbuf* msg = (struct msgbuf*)malloc(sizeof(struct msgbuf) + bufSize);
    int status = msgrcv(this->msgId, msg, bufSize, msgType, 0);
    memcpy(buf, msg->mtext, bufSize);
    free(msg);
    if (status  == -1) {
        throw IpcException(errno);
    }
}



void MessageQueueBase::destroyMessageQueue() {
    int status = msgctl(this->msgId, IPC_RMID, 0);
    if (status  == -1) {
        throw IpcException(errno);
    }
}


MessageQueue::MessageQueue() {

}

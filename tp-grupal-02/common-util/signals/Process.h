#ifndef PROCESS_H
#define PROCESS_H

class Process {
public:
    Process();
    void start();
    void stop();
    bool isRunning();
private:
    bool running;
    virtual void work() = 0;
};

#endif // PROCESS_H

#ifndef PROCESS_H
#define PROCESS_H

class Process {
public:
    Process();
    void stop();
    bool isRunning();
private:
    bool running;
};

#endif // PROCESS_H

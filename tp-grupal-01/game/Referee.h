#ifndef CONCURRENTES_REFEREE_H
#define CONCURRENTES_REFEREE_H


#include "Table.h"

class Referee {
private:
    bool running;
    useconds_t interval;
    Table table;
public:
    Referee(Table aTable);
    ~Referee();

    void setInterval(const int interval_ms);
    void start();
    void stop();
    void run();

    void showSummary();
};


#endif //CONCURRENTES_REFEREE_H

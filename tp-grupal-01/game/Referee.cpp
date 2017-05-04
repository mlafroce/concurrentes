#include <unistd.h>
#include "Referee.h"
#include "../log/Log.h"

#define DEFAULT_INTERVAL 1000*1000 //1 second

Referee::Referee(Table aTable) : table(aTable), running(false), interval(DEFAULT_INTERVAL) {}

Referee::~Referee() {}

void Referee::setInterval(const int newInterval) {
    if (newInterval > 0) {
        this->interval = (useconds_t)(newInterval * 1000);
    }
}

void Referee::start() {
    this->running = true;
    this->run();
}

void Referee::stop() {
    this->running = false;
}

void Referee::run() {
    while (this->running) {
        this->showSummary();
        usleep(this->interval);
    }
}

void Referee::showSummary() {
    std::string message = "\n[REFEREE STATS]\n\t";
    Card lastCard = this->table.getLastCard();
    message += (lastCard.getNumber() > 0) ? "Última carta jugada: " + lastCard.toString() : "Aún no se ha jugado carta";
    message += "\n\t";
    message += "+------------+--------+\n\t";
    message += "| ID Jugador | Cartas |\n\t";
    message += "+------------+--------+";
    std::map<std::string,int> tableStats = this->table.stats();
    bool winner = false;
    for (auto const &entry : tableStats) {
        if (entry.first != "winner") {
            std::string id = entry.first;
            std::string numberOfCards = std::to_string(entry.second);
            message = message + "\n\t| " + id + "\t\t\t | " + numberOfCards + ((numberOfCards.length() > 1) ? "" : " ") + "\t  |";
        } else {
            winner = true;
        }
    }
    message += "\n\t+------------+--------+";
    if (winner) {
        message += "\n";
        int winnerId = tableStats["winner"];
        message += "===========================================================\n";
        message += "|----===== JUEGO FINALIZADO | Ganador: Jugador " + std::to_string(winnerId) + " =====----|\n";
        message += "===========================================================";
        this->stop();
    }
    LOG_INFO(message);
}



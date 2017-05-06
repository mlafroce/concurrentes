#include "Log.h"

#include <iostream>
#include <map>

#define FILE_LOG_IPCS "log.semaphore.ipc"

Log* Log::instance = NULL;
LockFile* Log::lockFile = NULL;
Semaphore* Log::mutexSTDOUT = NULL;

static std::map<LOG_LEVEL,std::string> LEVEL_STRING_COLOR = {
        {DEBUG, "DEBUG"},
        {WARNING, "\033[1;41mWARNING\033[0m"},
        {INFO, "\033[1;34mINFO\033[0m"},
        {ERROR, "\033[1;31mERROR\033[0m"},
};

static std::map<LOG_LEVEL,std::string> LEVEL_STRING = {
        {DEBUG, "DEBUG"},
        {WARNING, "WARNING"},
        {INFO, "INFO"},
        {ERROR, "ERROR"},
};

Log::Log() {
    showInStdOut = false;
    level = DEBUG;
    timePrecision = false;
    mutexSTDOUT = NULL;
}

Log::~Log() {
    if (lockFile != NULL) {
        lockFile->free();
        delete lockFile;
    }
    mutexSTDOUT = NULL;
    lockFile = NULL;
}

Log* Log::getInstance() {
    if (instance == NULL) {
        instance = new Log();
    }
    return instance;
}

void Log::deleteInstance() {
    Log::deleteMutex();
    delete instance;
    instance = NULL;
}

void Log::setLevel(LOG_LEVEL newLevel) {
    this->level = newLevel;
}

bool Log::setFile(const std::string &file_name) {
    lockFile = new LockFile(file_name);
    return (lockFile != NULL);
}

void Log::deleteMutex() {
    if (mutexSTDOUT != NULL) {
        mutexSTDOUT->Delete();
        delete mutexSTDOUT;
    }
    mutexSTDOUT = NULL;
}

void Log::showInSTDOUT(bool show) {
    if (show) {
        if (mutexSTDOUT == NULL) {
            mutexSTDOUT = new Semaphore(FILE_LOG_IPCS,'z',1);
        }
    } else {
        Log::deleteMutex();
    }
    this->showInStdOut = show;
}

void Log::write(const std::string &message, LOG_LEVEL logLevel) {
    if (lockFile == NULL){
        THROW_UTIL("[FATAL]. Cannot Log: Not file set `Log::setFile(const std::string &file_name)`");
    }
    if (logLevel <= this->level) {
        std::string time = (this->timePrecision) ? Utils::getTimeWithFormatAndPrecision() : Utils::getTimeWithFormat();
        std::string log_message = "[" + time + "][" +
			LEVEL_STRING[logLevel] + "]" + "[PID: " + std::to_string(getpid()) +
			"] " + message + "\n";

        if (this->showInStdOut) {
            mutexSTDOUT->wait();
        }

        lockFile->lock();
        lockFile->Write(log_message.c_str(),log_message.size());
        lockFile->free();

        if (this->showInStdOut){
            std::string log_message_colored = "[" + time + "][" + LEVEL_STRING_COLOR[logLevel] + "]" +
			"[PID: " + std::to_string(getpid()) + "] " +  message;
                std::cout << log_message_colored << std::endl;
            mutexSTDOUT->signal();
        }
    }
}

void Log::showTimePrecision(bool show) {
    this->timePrecision = show;
}


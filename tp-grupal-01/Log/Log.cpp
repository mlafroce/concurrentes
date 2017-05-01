#include "Log.h"
#include "../util/Utils.h"

#include <iostream>
#include <map>

Log* Log::instance = NULL;
LockFile* Log::lockFile = NULL;

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
}

Log::~Log() {
    if (lockFile != NULL) {
        lockFile->free();
        delete lockFile;
    }
    lockFile = NULL;
}

Log* Log::getInstance() {
    if (instance == NULL) {
        instance = new Log();
    }
    return instance;
}

void Log::deleteInstance() {
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

void Log::showInSTDOUT(bool show) {
    this->showInStdOut = show;
}

void Log::write(const std::string &message, LOG_LEVEL logLevel) {
    if (lockFile == NULL){
        Utils::throwError("[FATAL]. Cannot Log: Not file set `Log::setFile(const std::string &file_name)`");
    }
    if (logLevel <= this->level) {
        std::string log_message = Utils::getTimeWithFormat() + "[" + LEVEL_STRING[logLevel] + "] " + message + "\n";

        lockFile->lock();
        lockFile->Write(log_message.c_str(),log_message.size());
        lockFile->free();

        if (this->showInStdOut){
            std::string log_message_colored = Utils::getTimeWithFormat() + "[" + LEVEL_STRING_COLOR[logLevel] + "] " + message;
            std::cout << log_message_colored << std::endl;
        }
    }
}


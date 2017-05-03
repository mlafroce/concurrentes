//
// Created by tomi on 22/04/17.
//

#ifndef CONCURRENTES_LOG_H
#define CONCURRENTES_LOG_H

#include <string>
#include "../util/LockFile.h"
#include "../util/Utils.h"

enum LOG_LEVEL {
    ERROR, WARNING, INFO, DEBUG
};

class Log {
private:
    LOG_LEVEL level; //Default: DEBUG
    bool showInStdOut; //Default: False
    bool timePrecision; //Default: False (show microseconds)
    static Log *instance;
    static LockFile *lockFile;

    Log();
    ~Log();

public:
    static Log *getInstance();
    static void deleteInstance();

    void setLevel(LOG_LEVEL level);
    bool setFile(const std::string& file_name);
    void showInSTDOUT(bool show);
    void showTimePrecision(bool show);

    void write(const std::string& message, LOG_LEVEL);
    void write(const std::string& message){ write(message,level);};

    void error(const std::string& message) { write(message,ERROR);};
    void warning(const std::string& message){ write(message,WARNING);};
    void info(const std::string& message){ write(message,INFO);};
    void debug(const std::string& message){ write(message,DEBUG);};



};

/* Macro to LOG with line and file specification */
#define LOG(level,message) Log::getInstance()->write( Utils::generateFileMessage(__FILE__,__LINE__) + ": " + message,level);
#define LOG_DEBUG(message) LOG(DEBUG,message);
#define LOG_INFO(message) LOG(INFO,message);
#define LOG_WARNING(message) LOG(WARNING,message);
#define LOG_ERROR(message) LOG(ERROR,message);

#endif //CONCURRENTES_LOG_H

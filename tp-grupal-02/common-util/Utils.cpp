#include <iostream>
#include "Utils.h"
#include "Log.h"
#include <ctime>
#include <sys/ipc.h>
#include <cstring>
#include <sys/time.h>

#define IPC_FILES_FOLDER "ipcfiles"

bool Utils::ipcDirCreated = false;

void Utils::throwError(const std::string &message) {
    Log::getInstance()->error(message);
    //std::cerr << message << std::endl;
    throw message;
}

std::string Utils::getTimeWithFormat(std::string format) {
    time_t now = time(0);
    struct tm time_struct;
    char buf[80];
    time_struct = *localtime(&now);
    const char* format_to_strf = format.c_str();
    strftime(buf, sizeof(buf), format_to_strf, &time_struct);
    return std::string(buf);
}

std::string Utils::getTimeWithFormatAndPrecision(std::string format) {
    timeval curTime;
    gettimeofday(&curTime, NULL);
    int milli = (int)(curTime.tv_usec);

    char buffer [80];
    strftime(buffer, 80, format.c_str(), localtime(&curTime.tv_sec));

    char currentTime[84] = "";
    sprintf(currentTime, "%s.%d", buffer, milli);

    return std::string(currentTime);
}

std::string Utils::generateFileMessage(std::string file, int line) {
    file.erase(0,file.find("tp-grupal-02/") + std::string("tp-grupal-02/").size());
    return file + " (line " + std::to_string(line) + ")";
}

void checkFile(const std::string& file) {
    size_t index = file.find("/");
    if (index != -1) {
        THROW_UTIL("No se puede usar \"" + file + "\" para hacer ftok. No debe contener \"/\"");
    }

    size_t index2 = file.find("\\");
    if (index2 != -1) {
        THROW_UTIL("No se puede usar \"" + file + "\" para hacer ftok. No debe contener \"\\\"");
    }
}

void createFile(const std::string& file) {
    if ( access( file.c_str(), F_OK ) == -1) {
        //File not exist
        system(std::string("touch " + file).c_str());
        if ( access( file.c_str(), F_OK ) == -1) {
            THROW_UTIL("No se puede crear \"" + file + "\" para realizar ftok");
        }
    }
}

key_t Utils::generateKey(const std::string &file, const char letter) {
    checkFile(file);

    if (!ipcDirCreated) {
        system(std::string("mkdir -p " + std::string(IPC_FILES_FOLDER)).c_str());
        ipcDirCreated = true;
    }

    std::string file_to_ftok = std::string(IPC_FILES_FOLDER) + "/" + file;
    createFile(file_to_ftok);

    key_t key = ftok(file_to_ftok.c_str(),letter);
    if (key == -1) {
        THROW_UTIL(std::string("Error en ftok('" + file_to_ftok + "', '" + letter + "'): [") + std::to_string(errno) + "] : " + std::string(strerror(errno)) );
    }
    return key;
}

std::vector<std::string> Utils::splitString(std::string the_string, std::string delimiter) {
    char* string_char = const_cast<char*>(the_string.c_str());

    std::vector<std::string> splitVector;

    char* current = strtok( string_char,delimiter.c_str() );
    while(current != NULL) {
        splitVector.push_back(std::string(current));
        current = strtok( NULL,delimiter.c_str() );
    }
    return splitVector;
}

int Utils::randomInt(const int a, const int b) {
    if (a >= b) {
        THROW_UTIL( "Parametros invalidos en Utils::randomInt(a = " + std::to_string(a) + ",b = " + std::to_string(b) + "): 'a' debe ser menor a 'b'" );
    }
    int maxValue = (b - a) + 1;
    srand ( (unsigned int)time(NULL) );
    return a + rand() % maxValue; // In the range a to b (inclusive)
}
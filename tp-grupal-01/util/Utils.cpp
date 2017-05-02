#include <iostream>
#include "Utils.h"
#include "../Log/Log.h"
#include <ctime>
#include <sys/ipc.h>
#include <cstring>

void Utils::throwError(const std::string &message) {
    LOG_ERROR(message);
    std::cerr << message << std::endl;
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

std::string Utils::generateFileMessage(std::string file, int line) {
    file.erase(0,file.find("tp-grupal-01/") + std::string("tp-grupal-01/").size());
    return file + " (line " + std::to_string(line) + ")";
}

key_t Utils::generateKey(const std::string &file, const char letter) {
    key_t key = ftok(file.c_str(),letter);
    if (key == -1) {
        Utils::throwError(std::string("Error on ftok(): [") + std::to_string(errno) + "] : " + std::string(strerror(errno)) );
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
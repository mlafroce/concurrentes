#ifndef CONCURRENTES_UTILS_H
#define CONCURRENTES_UTILS_H

#include <string>

class Utils {
public:
    static key_t generateKey(const std::string& file, const char letter);

    static void throwError(const std::string& message);
    static std::string getTimeWithFormat(std::string format = "[%Y/%m/%d %X]");
    static std::string generateFileMessage(std::string file, int line);
};


#endif //CONCURRENTES_UTILS_H

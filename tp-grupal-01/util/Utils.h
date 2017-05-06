#ifndef CONCURRENTES_UTILS_H
#define CONCURRENTES_UTILS_H

#include <string>
#include <vector>

class Utils {
private:
    static bool ipcDirCreated;
public:
    static key_t generateKey(const std::string& file, const char letter);

    static void throwError(const std::string& message);

    static std::string getTimeWithFormat(std::string format = "%Y/%m/%d %X");
    static std::string getTimeWithFormatAndPrecision(std::string format = "%Y/%m/%d %X");
    static std::string generateFileMessage(std::string file, int line);

    static std::vector<std::string> splitString(std::string the_string, std::string delimiter);

    static int randomInt(const int a = 0, const int b = 1000);
};

#define THROW_UTIL(message) Utils::throwError( Utils::generateFileMessage(__FILE__,__LINE__) + ": " + message);


#endif //CONCURRENTES_UTILS_H

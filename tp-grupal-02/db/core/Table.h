#ifndef CONCURRENTES_TABLE_H
#define CONCURRENTES_TABLE_H

#include <string>
#include <vector>
#include "../../common-util/LockFile.h"

typedef std::vector<std::string> t_row;
typedef std::vector<std::vector<std::string>> t_table;
typedef void (*collector)(t_row,t_table*,void*);

class Table {
private:
    LockFile lockFile;
    t_table table;
    void iterate(collector op, t_table* res, void* extra);

    std::string select(const std::string query);

    std::string insert(const std::string query);

    std::string update(const std::string query);

    std::string help();

    std::string generatePrettyResult(t_table res);

    t_row getHeader();

    std::string tableToString(t_table aTable);
public:
    Table();
    ~Table(){};

    std::string execute(const std::string& query);

};


#endif //CONCURRENTES_TABLE_H

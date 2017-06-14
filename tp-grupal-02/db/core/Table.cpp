#include "Table.h"
#include "../../common-util/Utils.h"
#include "../utils/TextTable.h"
#include <regex>
#include <fstream>

#define FILE "personas.db"

Table::Table() : lockFile(FILE) {}

void Table::iterate(collector op, t_table *res, void* extra) {
    lockFile.readLock();
        std::ifstream input(FILE);
        for( std::string line; getline( input, line ); ) {
            t_row v_line = Utils::splitString(line,",");
            op(v_line,res,extra);
        }
    lockFile.readFree();
}

std::string Table::insert(const std::string query) {
    std::regex r_insert("\\(\"([^\"]*)\",\"([^\"]*)\",\"([^\"]*)\"\\)");
    std::smatch sm;
    if (std::regex_search(query,sm,r_insert) && sm.size() == 4) {
        std::string buffer = sm[1].str() + "," + sm[2].str() + "," + sm[3].str() + "\n";
        lockFile.lock();
            lockFile.Write(buffer);
        lockFile.free();
        return "Query OK, 1 row affected (0.01 sec)";
    }
    return "Query Error, 0 row affected.\n"
            " Expected:\t`insert values(\"<<nombre>>\",\"<<apellido>>\",\"<<telefono>>\")`\n"
            " Get:\t\t`" + query + "` (" + std::to_string(sm.size()) + " match)";
}

std::string Table::update(const std::string query) {
    //TODO: Alguna forma de reemplazar en el archivo.
    return "[NOT IMPLEMENTED]";
}

t_row Table::getHeader() {
    return {"nombre","direccion","telefono"};
}

std::string Table::generatePrettyResult(t_table res) {
    TextTable t;
    for (auto colName : this->getHeader()) {
        t.add(colName);
    }
    t.endOfRow();

    for (auto row : res) {
        for (auto col : row) {
            t.add(col);
        }
        t.endOfRow();
    }
    t.setAlignment(0,TextTable::Alignment::RIGHT);
    t.setAlignment(1,TextTable::Alignment::RIGHT);
    t.setAlignment(2,TextTable::Alignment::RIGHT);
    std::ostringstream stream;
    stream << t << std::endl << res.size() << " rows";
    return stream.str();
}

void collectAll(t_row row, t_table* table, void* extra_arg = NULL) {
    table->push_back(row);
}

void collectByName(t_row row, t_table* table, void *extra_arg) {
    std::string match_name = *(std::string*)extra_arg;
    if (row[0] == *(std::string*)extra_arg) {
        table->push_back(row);
    }
}


std::string Table::select(const std::string query) {
    std::regex r_select("nombre ?= ?\"([^\"]*)\"");
    std::smatch sm;
    bool byName = false;
    std::string name;
    if (std::regex_search(query,sm,r_select)) {
        name = sm[1];
        byName = true;
    }

    t_table res;
    if (byName) {
        this->iterate(&collectByName,&res,&name);
    } else {
        this->iterate(&collectAll,&res,NULL);
    }
    return generatePrettyResult(res);
}

std::string Table::execute(const std::string &query) {
    std::regex r_select("^select.*");
    if (std::regex_match(query,r_select)) {
        return select(query);
    }
    std::regex r_update("^update.*");
    if (std::regex_match(query,r_update)) {
        return update(query);
    }
    std::regex r_insert("^insert.*");
    if (std::regex_match(query,r_insert)) {
        return insert(query);
    }
    return "Syntax error in query";
}
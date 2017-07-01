#include "Table.h"
#include "../../common-util/Utils.h"
#include "../utils/TextTable.h"
#include "../../common-util/Log.h"
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

t_row Table::getHeader() {
    return {"nombre","direccion","telefono"};
}

std::string Table::generatePrettyResult(t_table res) {
    if (res.size() == 0) {
        return "Empty set (0.00 sec)";
    }
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

std::string Table::update(const std::string query) {
    t_table filter;
    this->iterate(&collectAll,&filter,NULL);
    bool isFilterName = false;
    std::regex r_filter("where nombre ?= ?\"([^\"]*)\"");
    std::string filterName = "";
    std::smatch sm;
    if (std::regex_search(query,sm,r_filter)) {
        filterName = sm[1];
        isFilterName = true;
    }
    LOG_DEBUG("Recolecto todas las filas (" + std::to_string(filter.size()) + ")");
    int indexCol = -1;
    std::string newColValue;
    std::regex r_cols_up("set (nombre|direccion|telefono) = \"([^\"]*)\"");
    std::smatch sm_cols_up;
    if (std::regex_search(query,sm_cols_up,r_cols_up)) {
        if (sm_cols_up.size() == 3) {
            std::string col = sm_cols_up[1];
            indexCol = (col == "nombre") ? 0 : ((col == "direccion") ? 1 : 2);
            newColValue = sm_cols_up[2];
        } else {
            LOG_DEBUG("Regex searh result: " + std::to_string(sm_cols_up.size()) );
            return "Syntax error in update query";
        }
    } else {
        return "Syntax error in update query";
    }
    LOG_DEBUG("Modifico columna " + std::to_string(indexCol) + " con nuevo valor \"" + newColValue + "\"");
    int counter = 0;
    t_table finalTable;
    for (t_row &row : filter) {
        if (!isFilterName || row[0] == filterName) {
            row[indexCol] = newColValue;
            counter++;
        }
        finalTable.push_back(row);
    }
    LOG_DEBUG("Se van a modificar " + std::to_string(finalTable.size()) + " filas");
    if (counter > 0) {
        lockFile.lock();
            lockFile.cleanFile();
            lockFile.WriteFromStart(tableToString(finalTable));
        lockFile.free();
    }
    return "Query OK, " + std::to_string(counter) + " row affected (0.01 sec)";
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
    if (query == "exit") {
        return "Goodbye";
    }

    if (query == "help") {
        return this->help();
    }
    return "Syntax error in query";
}

std::string Table::help() {
    std::string help = "";
    help += ">>>> TPC I - Help <<<<\n\n\n";
    help += "* Insert \n -> insert values(\"<<nombre>>\",\"<<apellido>>\",\"<<telefono>>\") \n\n";
    help += "* Select \n -> select * \n -> select nombre = \"<<nombre>>\"\n\n";
    help += "* Update \n -> update set nombre|direccion|telefono = <<nuevo valor>> [where nombre = \"<<nombre>>\"]\n\n";
    help += "* Exit \n -> exit \n\n";
    help += "\n";

    return help;
}

std::string Table::tableToString(t_table aTable) {
    std::string final = "";
    for (t_row& row : aTable) {
        final += row[0] + "," + row[1] + "," + row [2] + "\n";
    }
    return final;
}

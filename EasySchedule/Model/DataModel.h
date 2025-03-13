#pragma once
#include <QtCore/QDateTime>
#include "../Model/CustomDataStructures.h"
#include "../clogger/logger.h"
#include "../sqlite3.h"
#include "../ViewModel/ScheduleViewModel.h"
#include <string>
#include <variant>

#define OUT void*

typedef std::string table;

class DataModel {
    static sqlite3* _db;

public:

    static bool is_initialized;
    static bool is_error;
    static bool is_terminated;
    static table table_name;

    template <typename T>
    static int parseData(OUT saver_ptr, int argc, char** argv, char** col) {
        debug("Parsing data...args:" + std::to_string(argc));
        std::vector<T*>* saver = static_cast<std::vector<T*>*>(saver_ptr);
        saver->push_back(new T(argc, col, argv));
        debug("Parse complete.");
        return 0;
    }
    [[nodiscard]] static bool initialize();

    [[nodiscard]] static bool ensureDatabaseExists();

    [[nodiscard]] static bool ensureTableExists(const table& _table);

    template <typename T>
    static std::vector<T*>* read(const table& _table = table_name,
                                 const Range& limit = Range::zero,
                                 const std::vector<std::pair<const std::string&, const Sort&>>& sorts = std::vector<
                                     std::pair<const std::string&, const Sort&>>()) {
        std::vector<T*>* result = new std::vector<T*>();
        std::string command = "SELECT * FROM " + _table;
        if (limit != Range::zero) {
            if (std::get_if<bool>(&limit.end)) command += "OFFSET " + std::to_string(limit.begin);
            else
                command += " LIMIT " + std::to_string(limit.begin) + ", " + std::to_string(
                    std::get<unsigned>(limit.end));
        }
        if (!sorts.empty()) {
            command += " ORDER BY ";
            for (std::pair sort : sorts) { command += sort.first + (sort.second == asc ? "ASC" : "DESC") + ", "; }
            command.pop_back();
        }
        sqlite3_exec(_db, command.data(), parseData<T>, result, nullptr);
        return result;
    }

    static void save(const ScheduleViewModel &_schedule, const table &_table = table_name);
    static void update(const ScheduleViewModel &_schedule, const table &_table = table_name);
    static void remove(const ScheduleViewModel &_schedule, const table &_table = table_name);
    static void dispose() {
        is_terminated = true;
        is_initialized = false;
        sqlite3_close(_db);
    }
};

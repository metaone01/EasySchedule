#include "DataModel.h"
#include "../clogger/logger.h"

bool DataModel::is_initialized = false;
bool DataModel::is_error = false;
bool DataModel::is_terminated = false;
table DataModel::table_name = "schedule";
sqlite3* DataModel::_db = nullptr;

bool DataModel::initialize() {
    debug("Initializing database connection...");
    is_terminated = false;
    is_error = !ensureDatabaseExists();
    if (const int code = sqlite3_open("./data.db", &_db); code == SQLITE_OK) {
        debug("Database opened.");
        is_initialized = true;
        is_error |= !ensureTableExists("schedule");
    } else {
        error("Database could not be opened.error code:" + std::to_string(code));
        is_error = true;
    }
    debug("Database initialization done.");
    return !is_error;
}

bool DataModel::ensureDatabaseExists() {
    if (const std::ifstream f("./data.db"); f.good()) {
        debug("Database file already exists.");
        return true;
    }
    warning("Database file does not exist. Creating...");
    std::ofstream f("./data.db");
    if (f.fail()) {
        f.close();
        error("Could not create database file.");
        return false;
    }
    f.close();
    info("Database file created");
    return true;
}

bool DataModel::ensureTableExists(const table& _table) {
    const std::string command = "CREATE TABLE IF NOT EXISTS " + _table +
        "(Title TEXT UNIQUE PRIMARY KEY,Priority INT,Begin GLOB,End GLOB,Alarms GLOB,Description TEXT,IsFinished INT); ";
    char* err_msg;
    sqlite3_exec(_db, command.c_str(), nullptr, nullptr, &err_msg);
    if (err_msg != nullptr)
        error(err_msg);
    return err_msg == nullptr;
}

void DataModel::save(const ScheduleViewModel &_schedule, const table &_table)
{
    debug("Preparing save schedule...");
    std::string command = "INSERT INTO " + _table + " VALUES (";
    command += "'" + _schedule.title + "'," + std::to_string(_schedule.priority) + ",'" + _schedule.begin.
        toString("yyyy-MM-dd hh:mm:ss").toStdString() + "','" + _schedule.end.toString("yyyy-MM-dd hh:mm:ss").
                                                                          toStdString() + "',";
    std::string alarm_str;
    info(command);
    for (const QDateTime& t : _schedule.alarms) { alarm_str += t.toString().toStdString() + "\n"; }
    if (!alarm_str.empty()) alarm_str.pop_back();
    info(command);
    debug("Preparation complete.");
    command += "'" + alarm_str + "','" + _schedule.description + "',"+(_schedule.is_finished?"1":"0")+");";
    info(command);
    char* err = nullptr;
    sqlite3_exec(_db, command.data(), nullptr, nullptr, &err);
    if (err != nullptr)
        error(static_cast<std::string>("Save failed: ")+ err);
    else
        info("Save complete.");
}

void DataModel::update(const ScheduleViewModel &_schedule, const table &_table)
{
    debug("Preparing update schedule...");
    std::string command = "UPDATE " + _table + " SET Title=";
    command += "'" + _schedule.title + "',Priority=" + std::to_string(_schedule.priority) + ",Begin='" + _schedule.begin
        .toString("yyyy-MM-dd hh:mm:ss").toStdString() + "',End='" + _schedule.end.toString("yyyy-MM-dd hh:mm:ss").
                                                                               toStdString() + "',Alarms=";
    std::string alarm_str;
    info(command);
    for (const QDateTime& t : _schedule.alarms) { alarm_str += t.toString().toStdString() + "\n"; }
    if (!alarm_str.empty()) alarm_str.pop_back();
    info(command);
    debug("Preparation complete.");
    command += "'" + alarm_str + "',Description='" + _schedule.description + "',IsFinished="+(_schedule.is_finished?"1":"0")+" WHERE Title='" + _schedule.title + "';";
    info(command);
    char* err = nullptr;
    sqlite3_exec(_db, command.data(), nullptr, nullptr, &err);
    if (err != nullptr)
        error(static_cast<std::string>("Update failed: ")+ err);
    else
        info("Update complete.");
}

void DataModel::remove(const ScheduleViewModel &_schedule, const table &_table)
{
    const std::string command = "DELETE FROM " + _table + " WHERE Title='" + _schedule.title + "';";
    char* err = nullptr;
    sqlite3_exec(_db, command.data(), nullptr, nullptr, &err);
    if (err != nullptr)
        error(static_cast<std::string>("Delete failed: ")+ err);
    else
        info("Delete complete.");
}

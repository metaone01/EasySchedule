#pragma once
#include <QtCore/QDateTime>
#include "../Model/CustomDataStructures.h"
#include <vector>

class ScheduleViewModel {
public:
    explicit ScheduleViewModel(int argc, char** col, char** argv);
    explicit ScheduleViewModel(std::string _title,
                               Priority _priority,
                               QDateTime _begin,
                               QDateTime _end,
                               std::vector<QDateTime> _alarms,
                               std::string _description);
    std::string title;
    Priority priority;
    QDateTime begin;
    QDateTime end;
    std::vector<QDateTime> alarms;
    std::string description;
    bool is_finished;

    std::string toString() const;
};

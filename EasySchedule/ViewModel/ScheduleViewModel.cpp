#include "ScheduleViewModel.h"
#include "../Converter/serializer.h"

ScheduleViewModel::ScheduleViewModel(int argc, char** col, char** argv) : title{argv[0]},
                                                                          priority{
                                                                              static_cast<Priority>(std::stoi(argv[1]))
                                                                          },
                                                                          begin{QDateTime::fromString(argv[2],
                                                                                          "yyyy-MM-dd hh:mm:ss")},
                                                                          end{QDateTime::fromString(argv[3],
                                                                                          "yyyy-MM-dd hh:mm:ss")},
                                                                          alarms{
                                                                              *deserialize<QDateTime>(
                                                                                  argv[4],
                                                                                  '\n',
                                                                                  [](const std::string& s) {
                                                                                      return QDateTime::fromString(
                                                                                          s.data(),
                                                                                          "yyyy-MM-dd hh:mm:ss");
                                                                                  })
                                                                          },
                                                                          description{argv[5]},
                                                                          is_finished{0 == strcmp(argv[6], "true")} {}

ScheduleViewModel::ScheduleViewModel(std::string _title,
                                     const Priority _priority,
                                     QDateTime _begin,
                                     QDateTime _end,
                                     std::vector<QDateTime> _alarms,
                                     std::string _description) : title{std::move(_title)},
                                                                 priority{_priority},
                                                                 begin{std::move(_begin)},
                                                                 end{std::move(_end)},
                                                                 alarms{std::move(_alarms)},
                                                                 description{std::move(_description)},
                                                                 is_finished{false} {}

std::string ScheduleViewModel::toString() const {
    return "title: " + title + "\n" + "priority:" + priorityToString(priority) + "\n" + "begin:" + begin.toString().
        toStdString() + "\n" + "end:" + end.toString().toStdString() + "\n" + "alarms:[" + serialize<QDateTime>(
            alarms,
            ',',
            [](const QDateTime& t) -> std::string {
                return t.toString("yyyy-MM-dd hh:mm:ss").toStdString();
            }) + "]\n" + "description:" + description;
}
#pragma once

#include <QtWidgets/QScrollArea>
#include "../Model/DataModel.h"
#include "SingleScheduleView.h"

class TodayScheduleView : public QListBox<SingleScheduleView> {
    private:
    void loadSchedules() {
        QDateTime curr = QDateTime::currentDateTime();
        curr.setTime(QTime(0, 0, 0, 0));
        const std::string begin_time = curr.toString("yyyy-MM-dd hh:mm:ss").toStdString();
        curr.setTime(QTime(23, 59, 59, 0));
        const std::string end_time = curr.toString("yyyy-MM-dd hh:mm:ss").toStdString();
        const std::vector<ScheduleViewModel*>* data = DataModel::read<ScheduleViewModel>(
            DataModel::table_name,
            Range::zero,
            {{"IsFinished = 0"}, {"Begin < '" + end_time + "'"}, {"End > '" + begin_time + "'"}},
            {{"Begin", asc}, {"End", desc}});
        for (ScheduleViewModel* view_model : *data) { this->addItem(new SingleScheduleView(this, view_model)); }
        delete data;
    }

public:
    explicit TodayScheduleView(QWidget* parent = nullptr) : QListBox{parent} { loadSchedules(); }
};
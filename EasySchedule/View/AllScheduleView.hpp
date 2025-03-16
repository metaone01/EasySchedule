#pragma once

#include "../CustomControl/QListBox.hpp"
#include "SingleScheduleView.h"
#include "../Model/DataModel.h"

class AllScheduleView : public QListBox<SingleScheduleView> {
    void loadSchedules() {
        const std::vector<ScheduleViewModel*>* data = DataModel::read<ScheduleViewModel>(
            DataModel::table_name,
            Range::zero,
            {"IsFinished = 0"},
            {{"Begin", asc}, {"End", asc}});

        for (ScheduleViewModel* view_model : *data) { this->addItem(new SingleScheduleView(this, view_model)); }
        delete data;
        data = nullptr;
    }

public:
    explicit AllScheduleView(QWidget* parent = nullptr): QListBox{parent} { loadSchedules(); }
};
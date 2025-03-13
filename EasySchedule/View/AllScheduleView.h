#pragma once

#include <QtWidgets/QScrollArea>

#include "SingleScheduleView.h"

class AllScheduleView : public QWidget {
    Q_OBJECT private:
    QHBoxLayout* _layout;
    QScrollArea* _content_presenter;
    QVBoxLayout* _content_layout;
    std::vector<SingleScheduleView*>* _schedules;
    void loadSchedules();

public:
    explicit AllScheduleView(QWidget* parent = nullptr);
    void removeChild(SingleScheduleView* child);
    ~AllScheduleView() override;
};
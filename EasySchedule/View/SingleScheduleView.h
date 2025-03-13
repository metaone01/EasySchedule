#pragma once
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>

#include "../CustomControl/Expander.h"
#include "../ViewModel/ScheduleViewModel.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>

class SingleScheduleView : public Expander {
private:
    ScheduleViewModel* _view_model;
    QFormLayout* _layout;
    QLabel* _priority;
    QDateTimeEdit* _begin;
    QDateTimeEdit* _end;
    QTextEdit* _description;
    QPushButton* _delete;
public:
    explicit SingleScheduleView(QWidget* parent, ScheduleViewModel* view_model);
    ScheduleViewModel* getViewModel() const;
    ~SingleScheduleView() override;
};
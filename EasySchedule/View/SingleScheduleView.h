#pragma once
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>

#include "../CustomControl/Expander.h"
#include "../ViewModel/ScheduleViewModel.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include "../CustomControl/QListBox.hpp"

class SingleScheduleView : public Expander {
private:
    ScheduleViewModel* _view_model;
    QFormLayout* _layout;
    QLabel* _priority;
    QDateTimeEdit* _begin;
    QDateTimeEdit* _end;
    QTextEdit* _description;
    QPushButton* _finished;
    QPushButton* _delete;
public:
    explicit SingleScheduleView(QListBox<SingleScheduleView>* parent, ScheduleViewModel* view_model);
    [[nodiscard]] ScheduleViewModel* getViewModel() const;
    ~SingleScheduleView() override;
};

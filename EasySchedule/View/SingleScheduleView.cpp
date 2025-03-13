#include "SingleScheduleView.h"

#include "AllScheduleView.h"

SingleScheduleView::SingleScheduleView(QWidget* parent, ScheduleViewModel* view_model) : Expander{
        parent,
        view_model->title
    },
    _view_model{view_model},
    _layout{new QFormLayout(parent)},
    _priority{new QLabel(priorityToString(view_model->priority).data())},
    _begin{new QDateTimeEdit(view_model->begin)},
    _end{new QDateTimeEdit(view_model->end)},
    _description{new QTextEdit()},
    _delete{new QPushButton("删除")} {
    _description->setReadOnly(true);
    _description->setText(view_model->description.data());
    _begin->setReadOnly(true);
    _end->setReadOnly(true);
    _layout->addRow("优先级: ", _priority);
    _layout->addRow("开始时间: ", _begin);
    _layout->addRow("结束时间: ", _end);
    _layout->addRow("详情: ", _description);
    _layout->addWidget(_delete);
    connect(_delete,
            &QPushButton::clicked,
            this,
            [this,parent]() { dynamic_cast<AllScheduleView*>(parent)->removeChild(this); });
    this->_content->setLayout(_layout);
}

ScheduleViewModel* SingleScheduleView::getViewModel() const { return _view_model; }

SingleScheduleView::~SingleScheduleView() {
    delete _view_model;
    delete _layout;
    delete _priority;
    delete _begin;
    delete _end;
    delete _description;
}
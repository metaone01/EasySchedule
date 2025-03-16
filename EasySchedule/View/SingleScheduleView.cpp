#include "SingleScheduleView.h"
#include "../Model/DataModel.h"

SingleScheduleView::SingleScheduleView(QListBox<SingleScheduleView>* parent, ScheduleViewModel* view_model) : Expander{
        parent,
        view_model->title
    },
    _view_model{view_model},
    _layout{new QFormLayout()},
    _priority{new QLabel(priorityToString(view_model->priority).data())},
    _begin{new QDateTimeEdit(view_model->begin)},
    _end{new QDateTimeEdit(view_model->end)},
    _description{new QTextEdit()},
    _finished{new QPushButton("完成任务")},
    _delete{new QPushButton("删除")} {
    _description->setReadOnly(true);
    _description->setText(view_model->description.data());
    _begin->setReadOnly(true);
    _end->setReadOnly(true);
    _layout->addRow("优先级: ", _priority);
    _layout->addRow("开始时间: ", _begin);
    _layout->addRow("结束时间: ", _end);
    _layout->addRow("详情: ", _description);
    _layout->addWidget(_finished);
    _layout->addWidget(_delete);
    connect(_finished,
            &QPushButton::clicked,
            this,
            [this,parent] {
                _view_model->is_finished = true;
                DataModel::update(*_view_model);
                parent->removeItem(this);
            });

    connect(_delete,
            &QPushButton::clicked,
            this,
            [this,parent] {
                DataModel::remove(*_view_model);
                parent->removeItem(this);
            });
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
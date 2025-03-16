#include "NewScheduleView.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include "../Model/DataModel.h"
#include "../ViewModel/ScheduleViewModel.h"

NewScheduleView::NewScheduleView(QWidget* parent) : QWidget{parent},
                                                    _layout{new QVBoxLayout()},
                                                    _input_layout{new QFormLayout()},
                                                    _operate_layout{new QHBoxLayout()},
                                                    _title{new QLineEdit()},
                                                    _priority{new QComboBox()},
                                                    _begin{new QDateTimeEdit()},
                                                    _end{new QDateTimeEdit()},
                                                    _description{new QTextEdit()},
                                                    _save{new QPushButton("保存")},
                                                    _reset{new QPushButton("重置")} {
    _input_layout->addRow("标题:", _title);
    _input_layout->addRow("优先级:", _priority);
    _input_layout->addRow("开始时间:", _begin);
    _input_layout->addRow("结束时间:", _end);
    _input_layout->addRow("详细信息:", _description);
    _operate_layout->addWidget(_save);
    _operate_layout->addWidget(_reset);
    const QDateTime curr = QDateTime::currentDateTime();
    _priority->addItem("紧急重要", urgentImportant);
    _priority->addItem("紧急不重要", urgent);
    _priority->addItem("不紧急但重要", important);
    _priority->addItem("不紧急不重要", normal);
    _begin->setDateTime(curr);
    _end->setDateTime(curr);
    _layout->addLayout(_input_layout);
    _layout->addLayout(_operate_layout);
    _layout->setContentsMargins(5, 5, 5, 5);
    this->setLayout(_layout);
    initSave();
    initReset();
}

void NewScheduleView::initSave() {
    connect(_save, &QPushButton::clicked, this, [this]() {
        DataModel::save(ScheduleViewModel(_title->text().toStdString(),
                                          _priority->currentData().value<Priority>(),
                                          _begin->dateTime(),
                                          _end->dateTime(),
                                          std::vector<QDateTime>{},
                                          _description->toPlainText().toStdString()));
        _title->clear();
        _description->clear();
    });
}

void NewScheduleView::initReset() {
    connect(_reset,
            &QPushButton::clicked,
            this,
            [this]() {
                _title->clear();
                _description->clear();
            });
}

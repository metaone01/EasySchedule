#include "AllScheduleView.h"

#include "../CustomControl/Expander.h"
#include "../Model/DataModel.h"
#include "../ViewModel/ScheduleViewModel.h"
#include "SingleScheduleView.h"

void AllScheduleView::loadSchedules() {
    const std::vector<ScheduleViewModel*>* data = DataModel::read<ScheduleViewModel>();

    for (ScheduleViewModel* view_model : *data) {
        _schedules->push_back(new SingleScheduleView(this, view_model));
        _content_layout->addWidget(_schedules->back());
    }
    delete data;
}

AllScheduleView::AllScheduleView(QWidget* parent) : QWidget{parent},
                                                    _layout{new QHBoxLayout(this)},
                                                    _content_presenter{new QScrollArea(this)},
                                                    _content_layout{new QVBoxLayout(_content_presenter)},
                                                    _schedules(new std::vector<SingleScheduleView*>()) {
    _content_presenter->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _content_presenter->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    loadSchedules();
    _content_presenter->setLayout(_content_layout);
    _layout->addWidget(_content_presenter);
    this->setLayout(_layout);
}

AllScheduleView::~AllScheduleView() {
    while (!_schedules->empty()) {
        delete _schedules->back();
        _schedules->pop_back();
    }
}

void AllScheduleView::removeChild(SingleScheduleView* child) {
    _content_layout->removeWidget(child);
    for (unsigned int i = 0; i < _schedules->size(); ++i) {
        if (_schedules->at(i) == child) {
            _schedules->erase(_schedules->begin() + i);
            break;
        }
    }
    DataModel::remove(*child->getViewModel());
    delete child;
}
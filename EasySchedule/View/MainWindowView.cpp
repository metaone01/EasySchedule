#include "MainWindowView.h"
#include "AllScheduleView.h"
#include "ConfigView.h"
#include "NewScheduleView.h"
#include "TodayScheduleView.h"

MainWindowView::MainWindowView(QWidget* parent) : QMainWindow{parent} {
    _content_presenter = new TabControl();
    _content_presenter->addPair<NewScheduleView>(new QPushButton("新建日程"));
    _content_presenter->addPair<AllScheduleView>(new QPushButton("所有日程"));
    _content_presenter->addPair<TodayScheduleView>(new QPushButton("今日日程"));
    _content_presenter->addPair<ConfigView>(new QPushButton("设置"));
    _content_presenter->getHeader()->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    // _content_presenter
    _content_presenter->show();
}
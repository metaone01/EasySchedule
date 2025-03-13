#include "TabControl.h"
#include "../clogger/logger.h"

TabControl::TabControl(QWidget* parent, QLayout* tab_strip_placement) : QWidget{parent},
                                                                        _layout{new QHBoxLayout()},
                                                                        _content_presenter{nullptr} {
    _header = new QWidget();
    _header->setBaseSize(200, 200);
    _header->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    _tab_strip_placement = tab_strip_placement;
    _header->setLayout(_tab_strip_placement);
    debug("TabControl Header Initialized");
    _layout->addWidget(_header);
    this->setContent(new QWidget());
    this->setLayout(_layout);
    debug("TabControl Initialized");
}

QLayout* TabControl::getHeader() const { return _tab_strip_placement; }

void TabControl::addHeader(QPushButton* header) { _tab_strip_placement->addWidget(header); }

void TabControl::setContent(QWidget* content) {
    delete _content_presenter;
    _content_presenter = content;
    content->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _layout->addWidget(_content_presenter);
}
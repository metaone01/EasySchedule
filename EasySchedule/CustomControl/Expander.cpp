﻿#include "Expander.h"

Expander::Expander(QWidget* parent, const std::string& header, QWidget* content) : QWidget{parent},
    _layout{new QVBoxLayout()},
    _header{new QPushButton()},
    _content{content} {
    _header->setText(header.data());
    _layout->addWidget(_header);
    _layout->addWidget(_content);
    _content->hide();
    setConnection();
    this->setLayout(_layout);
}

void Expander::setConnection() {
    connect(this->_header, &QPushButton::clicked, this, [this]() { _content->setHidden(!_content->isHidden()); });
}

void Expander::setHeader(const std::string& text) const { _header->setText(text.data()); }

void Expander::setContent(QWidget* content) {
    _content = content;
    _layout->addWidget(content);
    setConnection();
}
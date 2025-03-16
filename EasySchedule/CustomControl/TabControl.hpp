#pragma once
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

#include "../clogger/logger.h"

class TabControl : public QWidget {
    Q_OBJECT private:
    QHBoxLayout* _layout;
    QWidget* _header;
    QWidget* _content_presenter;
    QLayout* _tab_strip_placement;

public:
    explicit TabControl(QWidget* parent = nullptr, QLayout* tab_strip_placement = new QVBoxLayout()) : QWidget{parent},
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

    [[nodiscard]] QLayout* getHeader() const { return _tab_strip_placement; }

    template <typename T>
    void addPair(QPushButton* header) {
        _tab_strip_placement->addWidget(header);
        debug("Button Added:" + header->text().toStdString());
        connect(header, &QPushButton::clicked, this, [this]() { this->setContent(new T(this)); });
    }

    void addHeader(QPushButton* header) { _tab_strip_placement->addWidget(header); }

    void setContent(QWidget* content) {
        delete _content_presenter;
        _content_presenter = content;
        content->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        _layout->addWidget(_content_presenter);
    }
};

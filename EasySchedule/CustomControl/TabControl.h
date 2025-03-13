#pragma once
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

#include "../clogger/logger.h"
// #include "../clogger/logger.h"

class TabControl : public QWidget {
    Q_OBJECT private:
    QHBoxLayout* _layout;
    QWidget* _header;
    QWidget* _content_presenter;
    QLayout* _tab_strip_placement;

public:
    explicit TabControl(QWidget* parent = nullptr, QLayout* tab_strip_placement = new QVBoxLayout());
    [[nodiscard]] QLayout* getHeader() const;

    template <typename T>
    void addPair(QPushButton* header) {
        _tab_strip_placement->addWidget(header);
        debug("Button Added:" + header->text().toStdString());
        connect(header,
                &QPushButton::clicked,
                this,
                [this]() {
                    delete this->_content_presenter;
                    this->_content_presenter = new T();
                    this->_content_presenter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                    this->_layout->addWidget(_content_presenter);
                    _content_presenter->show();
                    // info("Content Added.");
                });
    }

    void addHeader(QPushButton* header);
    void setContent(QWidget* content);
};

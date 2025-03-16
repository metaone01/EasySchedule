#pragma once

#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include "../clogger/logger.h"

template <typename T>
class QListBox : public QScrollArea {
private:
    QWidget* _content_presenter;
    QLayout* _layout;
    std::vector<T*> _items;

public:
    explicit QListBox(QWidget* parent = nullptr,
                      QLayout* orientation = new QVBoxLayout(),
                      const Qt::Alignment align = Qt::AlignTop) : QScrollArea{parent},
                                                                  _content_presenter{new QWidget()},
                                                                  _layout{orientation},
                                                                  _items{std::vector<T*>()} {
        debug("Initializing ListBox");
        _content_presenter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        _layout->setAlignment(align);
        _content_presenter->setLayout(_layout);
        this->setWidget(_content_presenter);
        this->setWidgetResizable(true);
        debug("ListBox initialization complete");
    }

    void removeItem(unsigned index) {
        _layout->removeWidget(_items[index]);
        delete _items[index];
        _items.erase(_items.begin() + index);
    }

    void removeItem(T* child) {
        _layout->removeWidget(child);
        for (unsigned int i = 0; i < _items.size(); ++i) {
            if (_items.at(i) == child) {
                _items.erase(_items.begin() + i);
                break;
            }
        }
        delete child;
    }

    void addItem(T* child) {
        _items.push_back(child);
        _layout->addWidget(child);
        _content_presenter->adjustSize();
        child->show();
        debug("Added item.Now there are "+std::to_string(_layout->count())+"items.");
    }

    ~QListBox() override {
        while (!_items.empty()) {
            delete _items.back();
            _items.pop_back();
        }
        delete _content_presenter;
        _content_presenter = nullptr;
    }
};
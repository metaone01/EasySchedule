#pragma once
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

class Expander : public QWidget {
    Q_OBJECT private:
    QVBoxLayout* _layout;
    QPushButton* _header;
    void setConnection();
protected:
    QWidget* _content;

public:
    explicit Expander(QWidget* parent = nullptr, const std::string& header = "", QWidget* content = new QWidget());
    void setHeader(const std::string& text) const;
    void setContent(QWidget* content);
};
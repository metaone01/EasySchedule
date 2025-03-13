#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>

class NewScheduleView : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* _layout;
    QFormLayout *_input_layout;
    QHBoxLayout* _operate_layout;
    QLineEdit* _title;
    QComboBox *_priority;
    QDateTimeEdit *_begin;
    QDateTimeEdit *_end;
    // ListBox<QDateTimeEdit> *_alarms;
    QTextEdit* _description;
    QPushButton* _save;
    QPushButton* _reset;
    void initSave();
    void initReset();
public:
    explicit NewScheduleView(QWidget* parent = nullptr);
};
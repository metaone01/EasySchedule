#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "../CustomControl/TabControl.h"
    
class MainWindowView : public QMainWindow
{
    Q_OBJECT
private:
    TabControl *_content_presenter;
    QHBoxLayout *_layout;
public:
    explicit MainWindowView(QWidget *parent=nullptr);
};

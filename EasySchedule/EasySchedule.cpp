// #define UNITTEST
#include <QtWidgets/QApplication>

#include "clogger/logger.h"
#include "Model/DataModel.h"
#include "View/MainWindowView.h"
#ifdef UNITTEST
#include <gtest/gtest.h>
#include "UnitTest/ConverterTest.h"
#include "UnitTest/ScheduleViewModelTest.h"
    int main(int argc, char* argv[]) {
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
#else
int main(int argc, char* argv[]) {
    logger::init(true);
    if (!DataModel::initialize()) {
        fatal("Database initialization failed.");
        _exit(1);
    }
    QApplication a(argc, argv);
    MainWindowView w;
    // w.show();
    return QApplication::exec();
}
#endif
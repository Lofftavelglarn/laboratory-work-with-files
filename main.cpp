#include "fileapplication.h"
#include "filelogger.h"
#include <QCoreApplication>

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);
    FileLogger* logger = new FileLogger(&a);
    FileApplication::getInstance(logger, &a);
    return a.exec();
}

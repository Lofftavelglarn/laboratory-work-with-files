#include <QCoreApplication>
#include "fileapplication.h"
#include "filelogger.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FileLogger* logger = new FileLogger(&a);
    FileApplication fileApp = FileApplication(logger, &a);
    return a.exec();
}

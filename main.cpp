#include <QCoreApplication>
#include<fileapplication.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FileApplication fileApp = FileApplication(&a);
    return a.exec();
}

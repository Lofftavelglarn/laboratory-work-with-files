#include "filelogger.h"

FileLogger::FileLogger(QObject *parent): QObject{parent}{

}

void FileLogger::logging(QString s){
    QTextStream textStreamOut(stdout);
    textStreamOut << s;
}

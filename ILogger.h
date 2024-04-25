#ifndef ILOGGER_H
#define ILOGGER_H
#include<QString>


class ILogger{
public:
    virtual void logging(QString s) = 0;
};
#endif // ILOGGER_H

#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "ILogger.h"
#include <QObject>
#include <QTextStream>

class FileLogger:public QObject, public ILogger
{
    Q_OBJECT
public:
    explicit FileLogger(QObject *parent = nullptr);
    virtual void logging(QString s) override;
};

#endif // FILELOGGER_H

#ifndef FILEAPPLICATION_H
#define FILEAPPLICATION_H

#include <QObject>
#include <QTimer>
#include <vector>
#include "IHandler.h"
#include "FileHandler.h"
#include "ILogger.h"


class FileApplication : public QObject
{
    Q_OBJECT
public:
    explicit FileApplication(ILogger* logger, QObject *parent = nullptr);
private:
    std::vector<IHandler*> handlers;
    QTimer *mainTimer;
    ILogger* logger;
    void handle();
public slots:
    void handleEvent(FileEvent fileEvent);
};

#endif // FILEAPPLICATION_H

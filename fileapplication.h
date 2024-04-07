#ifndef FILEAPPLICATION_H
#define FILEAPPLICATION_H

#include <QObject>
#include <QTimer>
#include <vector>
#include "IHandler.h"
#include "FileHandler.h"

class FileApplication : public QObject
{
    Q_OBJECT
public:
    explicit FileApplication(QObject *parent = nullptr);
    void handle();
private:
    std::vector<IHandler*> handlers;
    QTimer *mainTimer;
public slots:
    void handleEvent(FileEvent fileEvent);
};

#endif // FILEAPPLICATION_H

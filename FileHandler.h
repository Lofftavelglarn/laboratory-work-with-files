#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QTextStream>
#include <QFile>
#include "IHandler.h"
#include "fileevent.h"


class FileHandler:public QObject, public IHandler{
    Q_OBJECT
public:
    explicit FileHandler(QObject *parent = nullptr);

    QString getPath();
    void setPath(QString path);

    virtual void handle() override;
signals:
    void sendEvent(FileEvent fileEvent);
private:
    QString path;
    long long int size;
    bool firstRun = true;
    long long int previousSize;
    QString previousStatus;
    bool exist();
    long long int checkSize();
};

#endif // FILEHANDLER_H

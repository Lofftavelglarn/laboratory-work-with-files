#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "IHandler.h"
#include "fileevent.h"
#include <QFile>
#include <QObject>
#include <QTextStream>

class FileHandler : public QObject, public IHandler {
    Q_OBJECT
public:
    explicit FileHandler(QObject* parent = nullptr);

    virtual QString getPath() const override;
    void setPath(const QString& path);

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

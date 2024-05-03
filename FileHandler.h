#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "IHandler.h"
#include "fileevent.h"
#include <QFile>
#include <QObject>
#include <QTextStream>

class FileHandler : public IHandler {
    Q_OBJECT
public:
    explicit FileHandler(QObject* parent = nullptr, const QString& path = nullptr);

    virtual QString getPath() const override;

    virtual void handle() override;


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

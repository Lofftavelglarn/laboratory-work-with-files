#ifndef IHANDLER_H
#define IHANDLER_H

#include "fileevent.h"
#include <QObject>
#include <QString>

class IHandler: public QObject {
    Q_OBJECT
public:
    IHandler(QObject* parent = nullptr): QObject{parent} {};
    virtual void handle() = 0;
    virtual QString getPath() const = 0;

signals:
    void sendEvent(FileEvent fileEvent);
};

#endif // IHANDLER_H

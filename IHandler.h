#ifndef IHANDLER_H
#define IHANDLER_H

#include <QString>

class IHandler {
public:
    virtual void handle() = 0;
    virtual QString getPath() const = 0;
};

#endif // IHANDLER_H

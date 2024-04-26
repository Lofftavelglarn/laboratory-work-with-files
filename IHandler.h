#ifndef IHANDLER_H
#define IHANDLER_H

#include"fileevent.h"


class IHandler{
public:
    virtual void handle() = 0;
};

#endif // IHANDLER_H

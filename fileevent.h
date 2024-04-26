#ifndef FILEEVENT_H
#define FILEEVENT_H

#include <QString>

class FileEvent
{
public:
    FileEvent();
    QString path;
    enum Status{
        Deleted,
        Created,
        Edited,
        Exist,
        NotExist,
        None
    };
    Status status = None;
    long long int size;
    QString generateMessage();
};

#endif // FILEEVENT_H

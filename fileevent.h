#ifndef FILEEVENT_H
#define FILEEVENT_H

#include <QString>

class FileEvent {
public:
    FileEvent();
    enum Status{
        Deleted,
        Created,
        Edited,
        Exist,
        NotExist,
        None
    };
    FileEvent(const QString& path, Status status, long long size = 0);
    QString generateMessage();
    QString getPath() const;
    void setPath(const QString& newPath);

    Status getStatus() const;
    void setStatus(Status newStatus);

    long long getSize() const;
    void setSize(long long newSize);

private:
    QString path;
    Status status;
    long long int size;
};

#endif // FILEEVENT_H

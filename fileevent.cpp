#include "fileevent.h"

FileEvent::FileEvent() : status(None), size(0) {}

FileEvent::FileEvent(const QString& path, Status status, long long size)
    : path(path), status(status), size(size) {}

QString FileEvent::getPath() const { return path; }

FileEvent::Status FileEvent::getStatus() const { return status; }

long long FileEvent::getSize() const { return size; }

void FileEvent::setPath(const QString& newPath) { path = newPath; }

void FileEvent::setStatus(Status newStatus) { status = newStatus; }

void FileEvent::setSize(long long newSize) { size = newSize; }

QString FileEvent::generateMessage() {
    switch (status) {
    case Deleted: {
        QString deleted = QString("File \"%1\" deleted! \n").arg(path);
        return deleted;
    }
    case Created: {
        QString created = QString("File \"%1\" created! File size: %2 \n")
                              .arg(path)
                              .arg(size);
        return created;
    }
    case Exist: {
        QString exist =
            QString("File \"%1\" exists! File size: %2 \n").arg(path).arg(size);
        return exist;
    }
    case NotExist: {
        QString notExist = QString("File \"%1\" doesn't exist! \n").arg(path);
        return notExist;
    }
    case Edited: {
        QString edited = QString("File \"%1\" edited! New file size: %2 \n")
                             .arg(path)
                             .arg(size);
        return edited;
    }
    default: {
        return QString("Error!");
    }
    }
}

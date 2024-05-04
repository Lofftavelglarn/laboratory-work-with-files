#include "FileHandler.h"

FileHandler::FileHandler(QObject *parent, const QString &path): IHandler{parent}, path(path) {}

void FileHandler::handle() {
    FileEvent fileEvent = FileEvent(path);

    if (firstRun) {
        if (this->exist()) {
            long long int fileSize = this->checkSize();
            fileEvent.setSize(fileSize);
            fileEvent.setStatus(FileEvent::Exist);
            firstRun = false;
            previousStatus = "Exist";
            previousSize = fileSize;
        } else {
            fileEvent.setStatus(FileEvent::NotExist);
            firstRun = false;
            previousStatus = "NotExist";
        }
    } else {
        if ((previousStatus == "NotExist" || previousStatus == "Deleted") &&
            this->exist()) {
            fileEvent.setStatus(FileEvent::Created);
            long long fileSize = this->checkSize();
            fileEvent.setSize(fileSize);
            previousStatus = "Created";
            previousSize = fileSize;
        }

        if ((previousStatus != "NotExist" && previousStatus != "Deleted") &&
            !this->exist()) {
            fileEvent.setStatus(FileEvent::Deleted);
            previousStatus = "Deleted";
        }

        if ((previousStatus != "NotExist" && previousStatus != "Deleted")) {
            long long fileSize = this->checkSize();
            if (previousSize != fileSize) {
                fileEvent.setStatus(FileEvent::Edited);
                fileEvent.setSize(fileSize);
                previousStatus = "Edited";
                previousSize = fileSize;
            }
        }
    }

    if (fileEvent.getStatus() != FileEvent::None) {
        emit sendEvent(fileEvent);
    }
}

bool FileHandler::exist() {
    QFile file(this->path);
    return file.exists();
}

long long int FileHandler::checkSize() {
    QFile file(this->path);
    return file.size();
}

QString FileHandler::getPath() const { return path; }

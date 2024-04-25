#include <FileHandler.h>

FileHandler::FileHandler(QObject *parent): QObject{parent}{

}

void FileHandler::handle(){
    FileEvent fileEvent = FileEvent();
    fileEvent.path = this->path;

    if(firstRun == true){
        if(this->exist()){
            long long int fileSize = this->checkSize();
            fileEvent.size = fileSize;
            fileEvent.status = FileEvent::Exist;
            firstRun = false;
            previousStatus = "Exist";
            previousSize = fileSize;
        } else{
            fileEvent.status = FileEvent::NotExist;
            firstRun = false;
            previousStatus = QString("NotExist");
        }
    } else{
        if((previousStatus == QString("NotExist") || previousStatus == QString("Deleted")) && this->exist()){
            fileEvent.status = FileEvent::Created;
            previousStatus = "Created";
            long long int fileSize = this->checkSize();
            fileEvent.size = fileSize;
            previousSize = fileSize;
        }

        if((previousStatus != QString("NotExist") && previousStatus != QString("Deleted")) && !this->exist()){
            fileEvent.status = FileEvent::Deleted;
            previousStatus = "Deleted";
        }
        if(previousStatus != QString("NotExist") && previousStatus != QString("Deleted")){
            long long int fileSize = this->checkSize();
            if(previousSize != fileSize){
                fileEvent.status = FileEvent::Edited;
                previousStatus = "Edited";
                fileEvent.size = fileSize;
                previousSize = fileSize;
            }
        }
    }
    if(fileEvent.status != FileEvent::None){
        emit sendEvent(fileEvent);
    }
}

bool FileHandler::exist(){
    QFile file(this->path);
    return file.exists();
}

long long int FileHandler::checkSize(){
    QFile file(this->path);
    return file.size();
}

void FileHandler::setPath(QString path){
    this->path = path;
}

QString FileHandler::getPath(){
    return path;
}

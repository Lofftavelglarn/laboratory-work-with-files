#include "fileapplication.h"

FileApplication::FileApplication(ILogger* logger, QObject* parent)
    : QObject{parent}, logger(logger) {
    files = std::vector<IHandler*>();
}

void FileApplication::addFile(const QString &path){
    IHandler* file = new FileHandler(this, path);

    if(file) {
        files.push_back(file);
        connect(file, &IHandler::sendEvent, this,
                &FileApplication::handleEvent);
    }
}

void FileApplication::deleteFile(const QString &path){
       auto elem = files.begin();
       while(elem != files.end()){
           if((*elem)->getPath() == path){
               files.erase(elem);
               break;
           }
       }
}

bool FileApplication::checkFiles(const QString &path){
    bool pathExists = false;
    for (const auto& file : files) {
        if (file->getPath() == path) {
            pathExists = true;
            return pathExists;
        }
    }
    return pathExists;
}

void FileApplication::handle() {
    for (auto file : files) {
        file->handle();
    }
}

void FileApplication::handleEvent(FileEvent fileEvent) {
    if (logger) {
        logger->logging(fileEvent.generateMessage());
    } else {
        QTextStream textStreamOut(stdout);
        textStreamOut << "Warning: No logger configured. Event: "
                      << fileEvent.generateMessage() << "\n";
    }
}

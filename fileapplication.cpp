#include "fileapplication.h"

FileApplication::FileApplication(QObject *parent): QObject{parent}
{
    QTextStream textStreamOut(stdout);
    QTextStream textStreamIn(stdin);
    textStreamOut << "How many files do you need to monitor?" << Qt::endl;
    textStreamOut.flush();
    int numFiles;
    bool ok = false;

    while(!ok){
        textStreamOut << "Enter the number of your files: ";
        textStreamOut.flush();
        textStreamIn >> numFiles;
        if (textStreamIn.status() == QTextStream::Ok) {
            ok = true;
        } else{
            textStreamIn.resetStatus();
            textStreamIn.readLine();
            textStreamOut << "Invalid input. Please enter a valid number." << Qt::endl;
        }
    }

    handlers = std::vector<IHandler*>();

    for(int i = 0; i < numFiles; i++){
        FileHandler *fileHandler = new FileHandler(this);
        QString string;
        textStreamOut << "File " << i+1 << ": ";
        textStreamOut.flush();
        textStreamIn >> string;
        fileHandler->setPath(string);
        handlers.push_back(fileHandler);
        connect(fileHandler, &FileHandler::sendEvent, this, &FileApplication::handleEvent);
    }
    mainTimer = new QTimer(this);
    connect(mainTimer, &QTimer::timeout, this, &FileApplication::handle);
    mainTimer->start(100);
}

void FileApplication::handle(){
    for(auto x: handlers){
        x->handle();
    }
}

void FileApplication::handleEvent(FileEvent fileEvent){
    QTextStream textStreamOut(stdout);
    textStreamOut << fileEvent.generateMessage();
}

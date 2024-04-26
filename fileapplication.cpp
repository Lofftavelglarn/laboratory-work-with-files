#include "fileapplication.h"

FileApplication::FileApplication(ILogger *logger, QObject *parent): QObject{parent}
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
        if (textStreamIn.status() != QTextStream::Ok || numFiles <= 0) {
            textStreamIn.resetStatus();
            textStreamIn.readLine();
            textStreamOut << "Invalid input. Please enter a valid number." << Qt::endl;
        } else{
            ok = true;
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
        //добавить проверки одинаковых путей и правильности пути до файла
        handlers.push_back(fileHandler);

        connect(fileHandler, &FileHandler::sendEvent, this, &FileApplication::handleEvent);
    }
    this->logger = logger;
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
    logger->logging(fileEvent.generateMessage());
}

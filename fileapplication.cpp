#include "fileapplication.h"

FileApplication::FileApplication(ILogger* logger, QObject* parent)
    : QObject{parent}, logger(logger) {

    files = std::vector<IHandler*>();
    mainTimer = new QTimer(this);
    connect(mainTimer, &QTimer::timeout, this, &FileApplication::handle);
    mainTimer->start(100);
}

void FileApplication::configureFileApp() {
    QTextStream textStreamOut(stdout);
    QTextStream textStreamIn(stdin);
    textStreamOut << "How many files do you need to monitor?" << Qt::endl;
    textStreamOut.flush();

    int numFiles;
    bool ok = false;

    while (!ok) {
        textStreamOut << "Enter the number of your files: ";
        textStreamOut.flush();
        textStreamIn >> numFiles;
        if (textStreamIn.status() != QTextStream::Ok || numFiles <= 0) {
            textStreamIn.resetStatus();
            textStreamIn.readLine();
            textStreamOut << "Invalid input. Please enter a valid number." << Qt::endl;
        } else {
            ok = true;
        }
    }

    for (int i = 0; i < numFiles; ++i) {
        textStreamOut << "File " << i + 1 << ": ";
        textStreamOut.flush();

        QString path;
        textStreamIn >> path;

        bool pathExists = false;
        for (const auto& file : files) {
            if (file->getPath() == path) {
                pathExists = true;
                break;
            }
        }

        if (pathExists) {
            textStreamOut << "Path already exists. Please provide a unique path." << Qt::endl;
            --i;
        } else {
            IHandler* file = new FileHandler(this, path);

            if(file) {
                files.push_back(file);
                connect(file, &IHandler::sendEvent, this,
                        &FileApplication::handleEvent);
            }
        }
    }
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

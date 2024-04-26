#include "fileapplication.h"

FileApplication::FileApplication(ILogger* logger, QObject* parent)
    : QObject{parent} {
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
            textStreamOut << "Invalid input. Please enter a valid number."
                          << Qt::endl;
        } else {
            ok = true;
        }
    }

    QRegExp pathPattern(
        R"([A-Za-z]:\\([A-Za-z0-9_\- ]+\\)*[A-Za-z0-9_\- ]+\.[A-Za-z0-9]+)");

    for (int i = 0; i < numFiles; ++i) {
        QString path;
        textStreamOut << "File " << i + 1 << ": ";
        textStreamOut.flush();
        textStreamIn >> path;

        if (!pathPattern.exactMatch(path)) {
            textStreamOut
                << "Invalid path. Please ensure it follows the pattern: "
                   "Drive:\\folder\\file.extension"
                << Qt::endl;
            --i;
            continue;
        }

        bool pathExists = false;
        for (const auto& handler : this->handlers) {
            if (handler->getPath() == path) {
                pathExists = true;
                break;
            }
        }
        if (pathExists) {
            textStreamOut
                << "Path already exists. Please provide a unique path."
                << Qt::endl;
            --i;
        } else {
            auto fileHandler = new FileHandler(this);
            fileHandler->setPath(path);
            this->handlers.push_back(fileHandler);
            connect(fileHandler, &FileHandler::sendEvent, this,
                    &FileApplication::handleEvent);
        }
    }
    this->logger = logger;
    mainTimer = new QTimer(this);
    connect(mainTimer, &QTimer::timeout, this, &FileApplication::handle);
    mainTimer->start(100);
}

void FileApplication::handle() {
    for (auto x : handlers) {
        x->handle();
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

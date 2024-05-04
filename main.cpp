#include "fileapplication.h"
#include "filelogger.h"
#include <QCoreApplication>


void configureFileApp(FileApplication* fileApp) {
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

        bool pathExists = fileApp->checkFiles(path);

        if (pathExists) {
            textStreamOut << "Path already exists. Please provide a unique path." << Qt::endl;
            --i;
        } else {
            fileApp->addFile(path);
        }
    }
}

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);

    FileLogger* logger = new FileLogger(&a);

    FileApplication::getInstance(logger, &a);
    configureFileApp(&FileApplication::getInstance());

    QTimer* mainTimer = new QTimer(&FileApplication::getInstance());
    FileApplication::connect(mainTimer, &QTimer::timeout, &FileApplication::getInstance(), &FileApplication::handle);
    mainTimer->start(100);

    return a.exec();
}

#ifndef FILEAPPLICATION_H
#define FILEAPPLICATION_H

#include "FileHandler.h"
#include "IHandler.h"
#include "ILogger.h"
#include <QObject>
#include <QRegExp>
#include <QTimer>
#include <vector>

class FileApplication : public QObject {
    Q_OBJECT
public:
    static FileApplication* getInstance(ILogger* logger = nullptr,
                                        QObject* parent = nullptr) {
        static FileApplication instance(logger, parent);
        return &instance;
    }

    FileApplication(const FileApplication&) = delete;
    void operator=(const FileApplication&) = delete;

private:
    explicit FileApplication(ILogger* logger, QObject* parent = nullptr);

    std::vector<IHandler*> handlers;
    QTimer* mainTimer;
    ILogger* logger;

    void handle();

public slots:
    void handleEvent(FileEvent fileEvent);
};

#endif // FILEAPPLICATION_H

#ifndef FILEAPPLICATION_H
#define FILEAPPLICATION_H

#include "FileHandler.h"
#include "IHandler.h"
#include "ILogger.h"
#include <QObject>
#include <QTimer>
#include <vector>

class FileApplication : public QObject {
    Q_OBJECT
public:
    static FileApplication& getInstance(ILogger* logger = nullptr,
                                        QObject* parent = nullptr) {
        static FileApplication instance(logger, parent);
        return instance;
    }

    FileApplication(const FileApplication&) = delete;
    FileApplication operator=(const FileApplication&) = delete;

    bool checkFiles(const QString &path);
    void addFile(const QString &path);
    void deleteFile(const QString &path);
    void handle();

private:
    explicit FileApplication(ILogger* logger, QObject* parent = nullptr);

    std::vector<IHandler*> files;
    ILogger* logger;

public slots:
    void handleEvent(FileEvent fileEvent);
};

#endif // FILEAPPLICATION_H

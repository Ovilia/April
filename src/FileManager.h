#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QMap>
#include <QString>

#include "ModelManager.h"

struct FileErrorWarning
{
    QMap<unsigned int, QString> errorMap;
    QMap<unsigned int, QString> warningMap;

    QString getBrief();
};



class FileManager
{
public:
    // return true if read file successfully
    // result is the error and warning information returned
    static bool readFile(const QString fileName,
                         ModelManager& modelManager,
                         FileErrorWarning& result);

    // return true if write file successfully
    // writeReadMe determines if to write ReadMe information into the file
    // result is the error and warning information returned
    static bool writeFile(const QString fileName,
                          ModelManager &modelManager,
                          const bool writeReadMe,
                          FileErrorWarning& result);

private:
    FileManager();

    static const QString READ_ME_STR;

    static const QString ERROR_OPEN_FILE;
    static const QString ERROR_PRIMITIVE_NAME_COUNT;

    enum SegmentState {
        Seg_Init = 0,
        Seg_Primitive,
        Seg_Solid
    };
};

#endif // FILEMANAGER_H

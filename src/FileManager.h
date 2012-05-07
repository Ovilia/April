#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QMap>
#include <QString>

#include "ModelManager.h"

struct FileErrorWarning
{
    // line number and error or warning info
    QMap<unsigned int, QString> errorMap;
    QMap<unsigned int, QString> warningMap;

    // get brief description of error and warning info
    QString getBrief();

    static const unsigned int NO_LINE_NUMBER = 0;
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

    static const QString FAIL_OPEN_FILE;
    static const QString ILLEGAL_PRIMITIVE_NAME_COUNT;
    static const QString ILLEGAL_PRIMITIVE_TYPE;
    static const QString SOLID_NOT_FOUND;
    static const QString ILLEGAL_EXPRESSION;
    static const QString ILLEGAL_ATTRIBUTE_OF_PTYPE;
    static const QString ILLEGAL_ATTRIBUTE_VALUE;

    enum SegmentState {
        Seg_Init = 0,
        Seg_Primitive,
        Seg_Solid
    };

    // get attribute from a line, rememeber to check result before use
    static double attributeDouble(const int lineCount, const QString& line,
                                  FileErrorWarning& result);
    static int attributeInt(const int lineCount, const QString& line,
                                  FileErrorWarning& result);
    static Vector3d attributeVector3d(const int lineCount, const QString& line,
                                      FileErrorWarning& result);
};

#endif // FILEMANAGER_H

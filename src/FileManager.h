#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QDomDocument>
#include <QString>

#include "ModelManager.h"
#include "Vector3d.h"

class FileManager
{
public:
    // return true if read file successfully
    // result is the error and warning information returned
    static bool readFile(const QString fileName,
                         ModelManager& modelManager);

    // return true if write file successfully
    // result is the error and warning information returned
    static bool writeFile(const QString fileName,
                          ModelManager& modelManager);

private:
    FileManager();

    static const QString DOC_NAME;
    static const QString ROOT_NAME;

    static bool insertSolid(QDomNode sNode, ModelManager& modelManager);

    static void pmtDom(QDomDocument& doc, QDomElement& element,
                       APrimitive* pmt);
    static void vectorDom(QDomElement& element, const QString& name,
                          QDomDocument& doc, const Vector3d& vec,
                          const QString& xLabel = "x",
                          const QString& yLabel = "y",
                          const QString& zLabel = "z");
    static QDomElement solidDom(QDomDocument& doc, ASolid* solid);
    static void float4(QDomElement& element, const GLfloat* f);
};

#endif // FILEMANAGER_H

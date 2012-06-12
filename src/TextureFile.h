#ifndef TextureFILE_H
#define TextureFILE_H

#include <QString>

#include "Texture.h"

class TextureFile
{
public:
    static Texture readFile(QString filename);
    static void writeFile(const Texture& filename);

private:
    TextureFile();

    static const QString DOC_NAME;
    static const QString ROOT_NAME;
};

#endif // TextureFILE_H

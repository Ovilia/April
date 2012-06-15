#ifndef TextureFILE_H
#define TextureFILE_H

#include <QString>

#include "Texture.h"

class TextureFile
{
public:
    static bool readFile(Texture* texture, const QString& filename);
    static bool writeFile(const Texture& texture, const QString& filename);

private:
    TextureFile();

    static const QString DOC_NAME;
    static const QString ROOT_NAME;
};

#endif // TextureFILE_H

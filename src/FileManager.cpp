#include "FileManager.h"

#include <QFile>
#include <QTextStream>

#include <QDebug>

#include "Solid/APrimitive.h"

const QString FileManager::READ_ME_STR =
        "# ---------------------------------------------------------------------------- #\n"\
        "# ---------------------------------------------------------------------------- #\n"\
        "#                                                                              #\n"\
        "#                                April Project                                 #\n"\
        "#                                                                              #\n"\
        "# ---------------------------------------------------------------------------- #\n"\
        "# ---------------------------------------------------------------------------- #\n"\
        "#                                                                              #\n"\
        "#         *.apr is the file format defined and used in April Project.          #\n"\
        "#               Author: Ovilia Zhang <OviliaZhang at hotmail.com>              #\n"\
        "#                                                                              #\n"\
        "# ---------------------------------------------------------------------------- #\n"\
        "# *.apr file format:                                                           #\n"\
        "# 1) All empty lines, lines with only spaces or tabs and lines with # in the   #\n"\
        "#    front will be ignored                                                     #\n"\
        "# 2) APrimitive should be declared in the following format:                    #\n"\
        "#    [cone/cube/cylinder/prism/pyramid/sphere] \"Primitive ...\" \"Solid ...\"     #\n"\
        "#    [width/height/depth/radius/slices/stacks/sideLength/length]=...           #\n"\
        "#    [translate/rotate/scale]={..., ..., ...}                                  #\n"\
        "#    - The first line of APrimitive should contain primitive type, name        #\n"\
        "#      of primitive and name of solid, otherwise, there'll be an error.        #\n"\
        "#      Defining a primitive of the same name with previous ones will cause an  #\n"\
        "#      error.                                                                  #\n"\
        "#    - The following lines of APrimitive could contain geometry attributes     #\n"\
        "#      (e.g.: width). If an attribute is not the one this type is supposed to  #\n"\
        "#      contain(e.g.: width attribute for a cone) or an attribute undefined     #\n"\
        "#      (e.g.: weight), there'll be an error. If an attribute is not defined    #\n"\
        "#      for this type, default value will be given.                             #\n"\
        "#    - The transform attributes(translate/rotate/scale) could be given.        #\n"\
        "#      Default value will be given if not.                                     #\n"\
        "# 3) ASolid should be declared in the following format:                        #\n"\
        "#    solid \"Solid ...\"                                                         #\n"\
        "#    [left/right]=\"Solid ...\"                                                  #\n"\
        "#    operation=[union/intersection/difference]                                 #\n"\
        "#    [translate/rotate/scale]={..., ..., ...}                                  #\n"\
        "#    - The first line of ASolid should contain solid and solid name, which     #\n"\
        "#      should be already defined in front of this line, otherwise, there'll be #\n"\
        "#      an error. Defining a solid of the same name with previous ones will     #\n"\
        "#      cause an error.                                                         #\n"\
        "#    - The following lines of ASolid should contain name of left and right     #\n"\
        "#      child, and the operation of this solid. Children should be defined      #\n"\
        "#      previously, otherwise, there'll be an error.                            #\n"\
        "#    - The format of transform attributes is the same with that of the         #\n"\
        "#      APrimitive.                                                             #\n"\
        "#                                                                              #\n"\
        "# An example of *.apr file: #\n"\
        "# cube \"Primitive 0\" \"Solid 0\"                                                 #\n"\
        "# width=1.5                                                                    #\n"\
        "# depth=1.2                                                                    #\n"\
        "# translate={0.4, 0.0, 0.2}                                                    #\n"\
        "# sphere \"Primitive 1\" \"Solid 1\"                                               #\n"\
        "# radius=2.0                                                                   #\n"\
        "# solid \"Solid 2\"                                                              #\n"\
        "# left=\"Solid 0\"                                                               #\n"\
        "# right=\"Solid 1\"                                                              #\n"\
        "# operation=union                                                              #\n"\
        "# translate={0.2, 0.0, 0.0}                                                    #\n"\
        "# rotate={30.0, 0, 60.0}                                                       #\n"
        "#                                                                              #\n"\
        "\n";

const QString FileManager::ERROR_OPEN_FILE = "Error in opening file";
const QString FileManager::ERROR_PRIMITIVE_NAME_COUNT =
        "Error in count of primitive and solid name when defining a primitive";

FileManager::FileManager()
{
}

bool FileManager::readFile(const QString fileName,
                           ModelManager& modelManager,
                           FileErrorWarning& result)
{
    modelManager.initialize();
    result.errorMap.clear();
    result.warningMap.clear();

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // open file successfully
        QTextStream stream(&file);
        int lineCount = 0;

        SegmentState segState = Seg_Init;
        APrimitive::PrimitiveType pmtType = APrimitive::PT_NONE;
        QString pmtName = "";
        QString solidName = "";
        double width = 0.0, height = 0.0, depth = 0.0;
        double radius = 0.0, sideLength = 0.0, length = 0.0;
        int slices = 0, stacks = 0;
        bool widthSetted = false, heightSetted = false,
                depthSetted = false, radiusSetted = false,
                sideLengthSetted = false, lengthSetted = false,
                slicesSetted = false, stacksSetted = false;

        while (!stream.atEnd()) {
            QString line = stream.readLine();
            ++lineCount;

            // ignore empty lines, lines with only spaces and tabs
            // and lines that start with #
            if (line.trimmed().isEmpty() || line.startsWith('#')) {
                continue;
            }
            line = line.trimmed();

            switch (segState) {
            case Seg_Init:
                // waiting for primitive or solid definition
                // i start from 1 because none is not legal
                for (int i = APrimitive::PT_NONE + 1;
                     i < APrimitive::PRIMITIVE_TYPE_COUNT; ++i) {
                    if (line.startsWith(APrimitive::PRIMITIVE_TYPE_NAME[i])) {
                        // primitive type
                        pmtType = (APrimitive::PrimitiveType)i;
                        line = line.mid(APrimitive::PRIMITIVE_TYPE_NAME[i].length());
                        qDebug()<<"mid:["<<line<<"]";
                        // primitive and solid name
                        QStringList names = line.split("\"", QString::SkipEmptyParts);
                        if (names.count() == 2) {
                            pmtName = names[0];
                            solidName = names[1];
                        } else {
                            result.errorMap.insert(lineCount, ERROR_PRIMITIVE_NAME_COUNT);
                            return false;
                        }
                        segState = Seg_Primitive;
                    }
                }
                break;

            case Seg_Primitive:

                break;

            case Seg_Solid:
                break;
            }
        }

        return true;
    } else {
        // fail to open file
        result.errorMap.insert(0, ERROR_OPEN_FILE);
        return false;
    }
}

bool FileManager::writeFile(const QString fileName,
                            const ModelManager& modelManager,
                            const bool writeReadMe,
                            FileErrorWarning& result)
{
    result.errorMap.clear();
    result.warningMap.clear();
}

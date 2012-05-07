#include "FileManager.h"

#include <QFile>
#include <QTextStream>

#include <QDebug>

#include "Solid/APrimitive.h"

QString FileErrorWarning::getBrief()
{
    QString brief = errorMap.count() + QString("errors, ")
            + warningMap.count() + QString("warnings\n")
            + QString("First error: ");
    if (errorMap.begin().key() != NO_LINE_NUMBER) {
        // add line number
        brief += QString("(Line ") + errorMap.begin().key() + QString(")");
    }
    brief += QString(" - ") + errorMap.begin().value();
    return brief;
}



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
        "#    - The transform attributes(translate/rotate/scale) could be given.        #\n"\
        "#      Default value will be given if not.                                     #\n"\
        "#    - The following lines of APrimitive could contain geometry attributes     #\n"\
        "#      (e.g.: width). If an attribute is not the one this type is supposed to  #\n"\
        "#      contain(e.g.: width attribute for a cone) or an attribute undefined     #\n"\
        "#      (e.g.: weight), there'll be an error. If an attribute is not defined    #\n"\
        "#      for this type, default value will be given.                             #\n"\
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
        "# An example of *.apr file:                                                    #\n"\
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

const QString FileManager::FAIL_OPEN_FILE = "Error in opening file";
const QString FileManager::ILLEGAL_PRIMITIVE_NAME_COUNT =
        "Error in count of primitive and solid name when defining a primitive";
const QString FileManager::ILLEGAL_PRIMITIVE_TYPE =
        "Primitive type is not supposed to be PT_NONE";
const QString FileManager::SOLID_NOT_FOUND =
        "Solid is not found with given primitive";
const QString FileManager::ILLEGAL_EXPRESSION =
        "Illegal expression";
const QString FileManager::ILLEGAL_ATTRIBUTE_OF_PTYPE =
        "Illegal attribute of current primitive type";
const QString FileManager::ILLEGAL_ATTRIBUTE_VALUE =
        "Illegal attribute value";

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
        QString leftName = "", rightName = "";
        ASolid::BoolOperation operation = ASolid::BO_PRIMITIVE;
        double width = 0.0, height = 0.0, depth = 0.0,
                radius = 0.0, sideLength = 0.0, length = 0.0;
        int slices = 0, stacks = 0, sideCount = 3;
        Vector3d rotate, translate, scale;
        bool widthSetted = false, heightSetted = false,
                depthSetted = false, radiusSetted = false,
                sideLengthSetted = false, lengthSetted = false,
                slicesSetted = false, stacksSetted = false,
                rotateSetted = false, translateSetted = false,
                scaleSetted = false;

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
                        if (pmtType == APrimitive::PT_NONE) {
                            // primitive is not supposed to be PT_NONE,
                            // ignore this and give a warning
                            result.warningMap.insert(lineCount,
                                                     ILLEGAL_PRIMITIVE_TYPE);
                            continue;
                        }
                        line = line.mid(APrimitive::
                                        PRIMITIVE_TYPE_NAME[i].length() + 2);
                        // primitive and solid name
                        QStringList names = line.split("\"", QString::SkipEmptyParts);
                        if (names.count() == 3) {
                            pmtName = names[0];
                            // names[1] is supposed to be space
                            solidName = names[2];
                        } else {
                            result.errorMap.insert(
                                        lineCount,
                                        ILLEGAL_PRIMITIVE_NAME_COUNT);
                            return false;
                        }

                        // init attributes
                        width = 0.0; height = 0.0; depth = 0.0;
                        radius = 0.0; sideLength = 0.0; length = 0.0;
                        slices = 0; stacks = 0; sideCount = 3;
                        widthSetted = false; heightSetted = false;
                        depthSetted = false; radiusSetted = false;
                        sideLengthSetted = false; lengthSetted = false;
                        slicesSetted = false; stacksSetted = false;
                        rotateSetted = false; translateSetted = false;
                        scaleSetted = false;
                        segState = Seg_Primitive;
                        break;
                    }
                }
                // check for solid
                if (line.startsWith("solid")) {
                    int pos = line.indexOf('\"');
                    int len = line.mid(sPos).indexOf('\"');
                    if (pos < 0 || len < 0) {
                        result.errorMap.insert(lineCount, ILLEGAL_EXPRESSION);
                        return false;
                    }
                    solidName = line.mid(pos, len);
                    segState = Seg_Solid;
                }
                break;

            case Seg_Primitive:
                // geometry attributes
                if (line.startsWith("radius", Qt::CaseInsensitive)) {
                    switch(pmtType) {
                    case APrimitive::PT_CONE:
                    case APrimitive::PT_CYLINDER:
                    case APrimitive::PT_SPHERE:
                    {
                        double getRadius = attributeDouble(
                                    lineCount, line, result);
                        if (result.errorMap.empty()) {
                            // no error
                            radius = getRadius;
                            radiusSetted = true;
                        } else {
                            return false;
                        }
                    }
                        break;
                    default:
                        // other primitive type is illegal, ignore current line
                        result.warningMap.insert(lineCount,
                                                 ILLEGAL_ATTRIBUTE_OF_PTYPE);
                    }
                } else if (line.startsWith("slices", Qt::CaseInsensitive)) {
                    switch(pmtType) {
                    case APrimitive::PT_CONE:
                    case APrimitive::PT_CYLINDER:
                    case APrimitive::PT_SPHERE:
                    {
                        int getSlices = attributeInt(
                                    lineCount, line, result);
                        if (result.errorMap.empty()) {
                            // no error
                            slices = getSlices;
                            slicesSetted = true;
                        } else {
                            return false;
                        }
                    }
                        break;
                    default:
                        // other primitive type is illegal, ignore current line
                        result.warningMap.insert(lineCount,
                                                 ILLEGAL_ATTRIBUTE_OF_PTYPE);
                    }
                } else if (line.startsWith("height", Qt::CaseInsensitive)) {
                    switch(pmtType) {
                    case APrimitive::PT_CONE:
                    case APrimitive::PT_CUBE:
                    case APrimitive::PT_CYLINDER:
                    {
                        double getHeight = attributeDouble(
                                    lineCount, line, result);
                        if (result.errorMap.empty()) {
                            // no error
                            height = getHeight;
                            heightSetted = true;
                        } else {
                            return false;
                        }
                    }
                        break;
                    default:
                        // other primitive type is illegal, ignore current line
                        result.warningMap.insert(lineCount,
                                                 ILLEGAL_ATTRIBUTE_OF_PTYPE);
                    }
                } else if (line.startsWith("width", Qt::CaseInsensitive)) {
                    switch(pmtType) {
                    case APrimitive::PT_CUBE:
                    {
                        double getWidth = attributeDouble(
                                    lineCount, line, result);
                        if (result.errorMap.empty()) {
                            // no error
                            width = getWidth;
                            widthSetted = true;
                        } else {
                            return false;
                        }
                    }
                        break;
                    default:
                        // other primitive type is illegal, ignore current line
                        result.warningMap.insert(lineCount,
                                                 ILLEGAL_ATTRIBUTE_OF_PTYPE);
                    }
                } else if (line.startsWith("depth", Qt::CaseInsensitive)) {
                    switch(pmtType) {
                    case APrimitive::PT_CUBE:
                    {
                        double getDepth = attributeDouble(
                                    lineCount, line, result);
                        if (result.errorMap.empty()) {
                            // no error
                            depth = getDepth;
                            depthSetted = true;
                        } else {
                            return false;
                        }
                    }
                        break;
                    default:
                        // other primitive type is illegal, ignore current line
                        result.warningMap.insert(lineCount,
                                                 ILLEGAL_ATTRIBUTE_OF_PTYPE);
                    }
                } else if (line.startsWith("length", Qt::CaseInsensitive)) {
                    switch(pmtType) {
                    case APrimitive::PT_PRISM:
                    {
                        double getLength = attributeDouble(
                                    lineCount, line, result);
                        if (result.errorMap.empty()) {
                            // no error
                            length = getLength;
                            lengthSetted = true;
                        } else {
                            return false;
                        }
                    }
                        break;
                    default:
                        // other primitive type is illegal, ignore current line
                        result.warningMap.insert(lineCount,
                                                 ILLEGAL_ATTRIBUTE_OF_PTYPE);
                    }
                } else if (line.startsWith("sideLength", Qt::CaseInsensitive)) {
                    switch(pmtType) {
                    case APrimitive::PT_PRISM:
                    case APrimitive::PT_PYRAMID:
                    {
                        double getLength = attributeDouble(
                                    lineCount, line, result);
                        if (result.errorMap.empty()) {
                            // no error
                            sideLength = getLength;
                            sideLengthSetted = true;
                        } else {
                            return false;
                        }
                    }
                        break;
                    default:
                        // other primitive type is illegal, ignore current line
                        result.warningMap.insert(lineCount,
                                                 ILLEGAL_ATTRIBUTE_OF_PTYPE);
                    }
                } else if (line.startsWith("sideCount", Qt::CaseInsensitive)) {
                    switch(pmtType) {
                    case APrimitive::PT_PRISM:
                    {
                        int getCount = attributeDouble(
                                    lineCount, line, result);
                        if (result.errorMap.empty()) {
                            // no error
                            // TODO: currently only 3 valid
                            if (getCount != 3) {
                                result.warningMap.insert(
                                            lineCount,
                                            "Currently lineCount only 3 valid");
                            }
                            sideCount = 3;
                        } else {
                            return false;
                        }
                    }
                        break;
                    default:
                        // other primitive type is illegal, ignore current line
                        result.warningMap.insert(lineCount,
                                                 ILLEGAL_ATTRIBUTE_OF_PTYPE);
                    }
                } else if (line.startsWith("stacks", Qt::CaseInsensitive)) {
                    switch(pmtType) {
                    case APrimitive::PT_SPHERE:
                    {
                        double getStacks = attributeDouble(
                                    lineCount, line, result);
                        if (result.errorMap.empty()) {
                            // no error
                            stacks = getStacks;
                            stacksSetted = true;
                        } else {
                            return false;
                        }
                    }
                        break;
                    default:
                        // other primitive type is illegal, ignore current line
                        result.warningMap.insert(lineCount,
                                                 ILLEGAL_ATTRIBUTE_OF_PTYPE);
                    }
                }
                break;

            case Seg_Solid:
                // left, right child, operation
                if (line.startsWith("left")) {
                    //QString left =
                }
                break;
            }

            // transform attributes
            if (segState == Seg_Primitive || segState == Seg_Solid) {
                if (line.startsWith("rotate")){
                    rotate = attributeVector3d(lineCount, line, result);
                    if (result.errorMap.empty()) {
                        rotateSetted = true;
                    } else {
                        return false;
                    }
                }else if (line.startsWith("translate")){
                    translate = attributeVector3d(lineCount, line, result);
                    if (result.errorMap.empty()) {
                        translateSetted = true;
                    } else {
                        return false;
                    }
                }else if (line.startsWith("scale")){
                    scale = attributeVector3d(lineCount, line, result);
                    if (result.errorMap.empty()) {
                        scaleSetted = true;
                    } else {
                        return false;
                    }
                }
            }
        }

        file.close();
        return true;
    } else {
        // fail to open file
        unsigned int lineNum = FileErrorWarning::NO_LINE_NUMBER;
        result.errorMap.insert(lineNum, FAIL_OPEN_FILE);
        return false;
    }
}

double FileManager::attributeDouble(
        const int lineCount, const QString& line, FileErrorWarning& result)
{
    int pos = line.indexOf('=');
    if (pos < 0) {
        // = not found, error
        result.errorMap.insert(lineCount, ILLEGAL_EXPRESSION);
        return 0.0;
    }
    bool toDoubleOk = false;
    double value = line.mid(pos).toDouble(&toDoubleOk);
    if (!toDoubleOk) {
        // error in toDouble
        result.errorMap.insert(lineCount, ILLEGAL_EXPRESSION);
        return 0.0;
    } else {
        if (value < EPSILON) {
            result.errorMap.insert(lineCount, ILLEGAL_ATTRIBUTE_VALUE);
            return 0.0;
        }
        return value;
    }
}

int FileManager::attributeInt(
        const int lineCount, const QString& line, FileErrorWarning& result)
{
    int pos = line.indexOf('=');
    if (pos < 0) {
        // = not found, error
        result.errorMap.insert(lineCount,
                               ILLEGAL_EXPRESSION);
        return 0;
    }
    bool toIntOk = false;
    int value = line.mid(pos).toInt(&toIntOk);
    if (!toIntOk) {
        // error in toDouble
        result.errorMap.insert(lineCount,
                               ILLEGAL_EXPRESSION);
        return 0;
    } else {
        if (value < 0) {
            result.errorMap.insert(lineCount, ILLEGAL_ATTRIBUTE_VALUE);
            return 0;
        }
        return value;
    }
}

Vector3d FileManager::attributeVector3d(const int lineCount,
                                       const QString& line,
                                       FileErrorWarning& result)
{
    int xPos = line.indexOf("={");
    int yPos = line.mid(xPos).indexOf(',') + xPos;
    int zPos = line.mid(yPos).indexOf(',') + yPos;
    if (xPos < 0 || yPos < 0 || zPos < 0) {
        // = not found, error
        result.errorMap.insert(lineCount,
                               ILLEGAL_EXPRESSION);
        return Vector3d();
    }
    bool xOk = false, yOk = false, zOk = false;
    int x = line.mid(xPos, yPos - xPos).toDouble(&xOk);
    int y = line.mid(yPos, zPos - yPos).toDouble(&yOk);
    int z = line.mid(zPos).toDouble(&zOk);
    if (!xOk || !yOk || !zOk) {
        // error in toDouble
        result.errorMap.insert(lineCount,
                               ILLEGAL_EXPRESSION);
        return Vector3d();
    } else {
        return Vector3d(x, y, z);
    }
}

bool FileManager::writeFile(const QString fileName,
                            ModelManager& modelManager,
                            const bool writeReadMe,
                            FileErrorWarning& result)
{
    result.errorMap.clear();
    result.warningMap.clear();

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        map<QString, APrimitive*>* primitiveMap =
                modelManager.getPrimitiveMap();
        map<QString, ASolid*>* solidMap =
                modelManager.getSolidMap();

        // write info of model if model is not empty
        if (!primitiveMap->empty() && !solidMap->empty()) {
            // write primitive info
            for (map<QString, APrimitive*>::iterator pIter =
                 primitiveMap->begin();
                 pIter != primitiveMap->end(); ++pIter) {
                // corresponding solid of this primitive
                ASolid* solid = modelManager.getSolidFromPmt(pIter->second);
                if (solid == 0) {
                    // solid of this primitive is not found
                    // fail to save model and give an error
                    unsigned int lineNum = FileErrorWarning::NO_LINE_NUMBER;
                    result.errorMap.insert(lineNum, SOLID_NOT_FOUND);
                    return false;
                }
                stream << pIter->second->toString(solid);
            }

            // write solid info
            for (map<QString, ASolid*>::iterator sIter =
                 solidMap->begin();
                 sIter != solidMap->begin(); ++sIter) {
                // only write those are not leaves, because leave solid
                // has been written in primitive
                if (!sIter->second->isLeave()) {
                    stream << sIter->second->toString();
                }
            }
        }

        // write read me
        if (writeReadMe) {
            stream << READ_ME_STR;
        }

        file.close();

        // model saved successfully
        modelManager.setModelSaved();

        return true;
    } else {
        // fail to open file
        unsigned int lineNum = FileErrorWarning::NO_LINE_NUMBER;
        result.errorMap.insert(lineNum, FAIL_OPEN_FILE);
        return false;
    }
}

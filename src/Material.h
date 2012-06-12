#ifndef MATERIAL_H
#define MATERIAL_H

#include <QtOpenGL>

class Material
{
public:
    Material();
    Material(const Material& material);

    void setAmbient(const GLfloat* newValue);
    void setDiffuse(const GLfloat* newValue);
    void setSpecular(const GLfloat* newValue);
    void setShiness(const GLfloat newValue);

    GLfloat* getAmbient() const;
    GLfloat* getDiffuse() const;
    GLfloat* getSpecular() const;
    GLfloat getShiness() const;

private:
    static const int COLOR_LENGTH = 4;
    static const GLfloat DEFAULT_AMBIENT[COLOR_LENGTH];
    static const GLfloat DEFAULT_DIFFUSE[COLOR_LENGTH];
    static const GLfloat DEFAULT_SPECULAR[COLOR_LENGTH];
    static const GLfloat DEFAULT_SHINESS;

    GLfloat ambient[COLOR_LENGTH];
    GLfloat diffuse[COLOR_LENGTH];
    GLfloat specular[COLOR_LENGTH];
    GLfloat shiness;
};

#endif // MATERIAL_H

#ifndef LIGHTING_H
#define LIGHTING_H

#include <QString>
#include <QtOpenGL>

#include "Material.h"
#include "Vector3d.h"

class Lighting : public Material
{
public:
    Lighting(GLuint id);
    Lighting(const Lighting& lighting);

    GLuint getId() const;

    bool getIsOn() const;
    void setIsOn(bool isOn);

    QString getName() const;
    void setName(QString name);

    const GLfloat* getPosition() const;
    void setPosition(GLfloat position[4]);

private:
    GLuint id;
    QString name;

    bool isOn;

    GLfloat position[4];
};

#endif // LIGHTING_H

#include "Lighting.h"

Lighting::Lighting(GLuint id) :
    Material(),
    id(id),
    isOn(false)
{
    name = "Light " + QString::number(id + 1);
    for (int i = 0; i < 4; ++i) {
        position[i] = 1.0f;
    }
}

Lighting::Lighting(const Lighting& lighting) :
    Material((Material)lighting),
    id(lighting.getId()),
    name(lighting.getName()),
    isOn(lighting.getIsOn())
{
    const GLfloat* pos = lighting.getPosition();
    for (int i = 0; i < 4; ++i) {
        position[i] = pos[i];
    }
}

GLuint Lighting::getId() const
{
    return id;
}

bool Lighting::getIsOn() const
{
    return isOn;
}

void Lighting::setIsOn(bool isOn)
{
    this->isOn = isOn;
}

QString Lighting::getName() const
{
    return name;
}

void Lighting::setName(QString name)
{
    this->name = name;
}

const GLfloat* Lighting::getPosition() const
{
    return position;
}

void Lighting::setPosition(GLfloat position[4])
{
    for (int i = 0; i < 4; ++i) {
        this->position[i] = position[i];
    }
}

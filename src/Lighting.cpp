#include "Lighting.h"

Lighting::Lighting(GLuint id) :
    Material(),
    id(id),
    isOn(false),
    cutOff(180.0)
{
    name = "Light " + QString::number(id + 1);
    for (int i = 0; i < 4; ++i) {
        position[i] = 1.0f;
        direction[i] = -1.0f;
    }
}

Lighting::Lighting(const Lighting& lighting) :
    Material((Material)lighting),
    id(lighting.getId()),
    name(lighting.getName()),
    isOn(lighting.getIsOn()),
    cutOff(lighting.getCutOff())
{
    const GLfloat* pos = lighting.getPosition();
    const GLfloat* dir = lighting.getDirection();
    for (int i = 0; i < 4; ++i) {
        position[i] = pos[i];
        direction[i] = dir[i];
    }
}

GLfloat Lighting::getCutOff() const
{
    return cutOff;
}

void Lighting::setCutOff(GLfloat cutOff)
{
    this->cutOff = cutOff;
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

const GLfloat* Lighting::getDirection() const
{
    return direction;
}

void Lighting::setDirection(GLfloat* direction)
{
    for (int i = 0; i < 4; ++i) {
        this->direction[i] = direction[i];
    }
}

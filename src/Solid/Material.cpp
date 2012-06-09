#include "Material.h"

const GLfloat Material::DEFAULT_AMBIENT[COLOR_LENGTH] = {1.0, 1.0, 1.0, 1.0};
const GLfloat Material::DEFAULT_DIFFUSE[COLOR_LENGTH] = {1.0, 1.0, 1.0, 1.0};
const GLfloat Material::DEFAULT_SPECULAR[COLOR_LENGTH] = {1.0, 1.0, 1.0, 1.0};
const GLfloat Material::DEFAULT_SHINESS = 32.0;

Material::Material()
{
    setAmbient(DEFAULT_AMBIENT);
    setDiffuse(DEFAULT_DIFFUSE);
    setSpecular(DEFAULT_SPECULAR);
    setShiness(DEFAULT_SHINESS);
}

void Material::setAmbient(const GLfloat* newValue)
{
    for (int i = 0; i < COLOR_LENGTH; ++i) {
        ambient[i] = newValue[i];
    }
}

void Material::setDiffuse(const GLfloat* newValue)
{
    for (int i = 0; i < COLOR_LENGTH; ++i) {
        diffuse[i] = newValue[i];
    }
}

void Material::setSpecular(const GLfloat* newValue)
{
    for (int i = 0; i < COLOR_LENGTH; ++i) {
        specular[i] = newValue[i];
    }
}

void Material::setShiness(const GLfloat newValue)
{
    shiness = newValue;
}

GLfloat* Material::getAmbient() const
{
    return (GLfloat*)ambient;
}

GLfloat* Material::getDiffuse() const
{
    return (GLfloat*)diffuse;
}

GLfloat* Material::getSpecular() const
{
    return (GLfloat*)specular;
}

GLfloat Material::getShiness() const
{
    return shiness;
}

void Material::setId(unsigned int id)
{
    mId = id;
}

unsigned int Material::getId() const
{
    return mId;
}

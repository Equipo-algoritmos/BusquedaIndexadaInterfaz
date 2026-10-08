#include "Persona.h"

Persona::Persona(QString c, QString n, int e)
{
    clave = c;
    nombre = n;
    edad = e;
}

int Persona::getEdad()
{
    return edad;
}

QString Persona::getNombre()
{
    return nombre;
}

QString Persona::getClave()
{
    return clave;
}

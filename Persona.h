#pragma once

#include <QString>

class Persona
{
private:
    QString clave;
    QString nombre;
    int edad;

public:
    Persona(QString c, QString n, int e);

    QString getClave();
    QString getNombre();
    int getEdad();
};

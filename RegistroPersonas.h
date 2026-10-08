#pragma once

#include "Persona.h"
#include <QString>
#include <QVector>

class RegistroPersonas
{
private:
    QVector<Persona> personas;
    QVector<int> indices;

    void construirindices();
    void cargarDatos(QString archivo);

public:
    RegistroPersonas(QString archivo);
    RegistroPersonas()=default;
    void agregarPersona(Persona persona);
    int getSize();
    Persona getPersona(int i);
    int buscar(QString buscado);
    void descargarRegistro(QString nombreA);
};

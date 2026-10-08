#include "Persona.h"
#include "RegistroPersonas.h"

#include <QFile>
#include <QTextStream>

int RegistroPersonas::buscar(QString buscado)
{
    if (buscado.isEmpty() || personas.isEmpty())
        return -1;

    if ((buscado[0] < QChar('A')) || (buscado[0] > QChar('Z')))
        return -1;

    int m = buscado[0].unicode() - QChar('A').unicode();
    int bajo = indices[m];
    int alto = indices[m + 1] - 1;

    while (bajo <= alto)
    {
        int medio = ((alto - bajo) / 2) + bajo;

        QString claveCentral =
            personas[medio].getClave();

        if (claveCentral == buscado)
            return medio;

        else if (claveCentral < buscado)
            bajo = medio + 1;

        else
            alto = medio - 1;
    }

    return -1;
}

void RegistroPersonas::construirindices()
{
    indices.fill(-1, 27);

    for (int i = 0; i < personas.size(); ++i)
    {
        QString clave =
            personas[i].getClave();

        int letra = clave[0].unicode() - QChar('A').unicode();

        if (indices[letra] == -1)
            indices[letra] = i;
    }

    indices[26] = personas.size();

    for (int letra = 25; letra >= 0; --letra)
    {
        if (indices[letra] == -1)
            indices[letra] = indices[letra + 1];
    }
}

Persona RegistroPersonas::getPersona(int i)
{
    return personas.at(i);
}

RegistroPersonas::RegistroPersonas(QString archivo)
{
    cargarDatos(archivo);
}



void RegistroPersonas::cargarDatos(QString archivo)
{
    QFile entrada(archivo);

    if (!entrada.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream texto(&entrada);

    while (!texto.atEnd())
    {
        QString linea = texto.readLine();

        QString clave = linea.section(';', 0, 0);
        QString nombre = linea.section(';', 1, 1);
        QString edadTexto = linea.section(';', 2);

        int edad = edadTexto.toInt();

        Persona nueva(clave, nombre, edad);

        personas.push_back(nueva);
    }

    construirindices();
}

void RegistroPersonas::descargarRegistro(QString nombreA){
    QFile archivo(nombreA);
    if(!archivo.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream salida(&archivo);
    for (Persona persona : personas) {
        salida<<persona.getClave()<<";"
               <<persona.getNombre()<<";"
               <<persona.getEdad()<<"\n";
    }
}

void RegistroPersonas::agregarPersona(Persona persona){
    personas.push_back(persona);
}

int RegistroPersonas::getSize()
{
    return static_cast<int>(personas.size());
}

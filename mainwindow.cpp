#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "RegistroPersonas.h"
#include <QFileDialog.h>
#include <QMessageBox>
#include <Qdir.h>
#include <QFileInfo>
#include <QtConcurrent/QtConcurrentRun>
#include <QFutureWatcher>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->BarArchivo->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSelect_clicked()
{
    QString archivo = QFileDialog::getOpenFileName(this, "open a file", QDir::currentPath(), "Archivos de texto (*.txt)");
    QMessageBox::information(this,"..",archivo);
    QFileInfo info(archivo);
    ui ->lblArchivo->setText(info.fileName());
    delete registro;
    registro = new RegistroPersonas(archivo);
    ui->txtClave->setFocus();
}

void MainWindow::on_txtClave_returnPressed()
{
    QString clave = ui->txtClave->text();
    if (clave==nullptr){
        return;
    }
    if (registro == nullptr){
        QMessageBox::information(this, "Buscar", "Primero debes subir un archivo");
        return;
    }
    int posicion = registro->buscar(clave);
    if (posicion == -1)
    {
        QMessageBox::information(this, "Buscar", "Clave no encontrada");
        return;
    }
    Persona persona = registro->getPersona(posicion);
    int fila = ui->tblArchivo->rowCount();
    ui->tblArchivo->insertRow(fila);
    ui->tblArchivo->setItem(
        fila, 0, new QTableWidgetItem(persona.getClave()));
    ui->tblArchivo->setItem(
        fila, 1, new QTableWidgetItem(persona.getNombre()));
    ui->tblArchivo->setItem(
        fila, 2, new QTableWidgetItem(
            QString::number(persona.getEdad())));
    ui->txtClave->clear();
}


void MainWindow::on_pushButton_clicked()
{
    on_txtClave_returnPressed();
}


void MainWindow::on_btnDescargar_clicked()
{
    QString ruta = QFileDialog::getSaveFileName(
        this, "Guardar registro", "registro.txt",
        "Archivos de texto (*.txt)");

    if (ruta.isEmpty())
        return;
    RegistroPersonas tabla;
    int filas = ui->tblArchivo->rowCount();
    for (int i=0;i<filas;i++) {
        QString Clave=ui->tblArchivo->item(i,0)->text();
        QString Nombre=ui->tblArchivo->item(i,1)->text();
        int Edad=ui->tblArchivo->item(i,2)->text().toInt();
        Persona persona(Clave,Nombre,Edad);
        tabla.agregarPersona(persona);
    }
    tabla.descargarRegistro(ruta);
}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "RegistroPersonas.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_txtClave_returnPressed();
private slots:
    void on_btnSelect_clicked();
    void on_pushButton_clicked();

    void on_txtClave_cursorPositionChanged(int arg1, int arg2);

    void on_btnDescargar_clicked();

private:
    RegistroPersonas *registro = nullptr;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

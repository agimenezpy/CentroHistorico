#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class About;
class Listado;
class BarrioForm;
class EncuestadorForm;

class MainWindow : public QMainWindow, private Ui::MainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);

private slots:
    void showAbout();
    void showListado();
    void hideListado();
    void showBarrio();
    void hideBarrio();
    void showEncuesta();
    void hideEncuesta();
    void showNuevo();

private:
    About *about;
    Listado *listado;
    BarrioForm *barrio;
    EncuestadorForm *encuesta;
};

#endif // MAINWINDOW_H

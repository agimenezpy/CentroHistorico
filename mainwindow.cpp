#include "mainwindow.h"
#include "about.h"
#include "listado.h"
#include "barrioform.h"
#include "encuestadorform.h"
#include "generalform.h"

#include <QMdiSubWindow>
#include <QSqlDatabase>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    setupUi(this);
    // Set Statusbar
    this->statusbar->showMessage("Iniciado");

    // Set Toolbar
    toolBar->addAction(actionNuevo);
    toolBar->addAction(actionBuscar);
    toolBar->addAction(actionBarrios);
    toolBar->addAction(actionEncuestadores);

    // Set Windows
    about = new About(this);
    listado = 0;
    barrio = 0;
    encuesta = 0;
}

void MainWindow::showListado() {
    if (listado == 0) {
        listado = new Listado;
        QMdiSubWindow *subWin = mdiArea->addSubWindow(listado, Qt::SubWindow);
        subWin->setAttribute(Qt::WA_DeleteOnClose);
        listado->setParent(subWin);
    }
    listado->setWindowState(Qt::WindowMaximized);
    listado->show();
    listado->setFocus(Qt::ActiveWindowFocusReason);
    connect(listado, SIGNAL(destroyed()), this, SLOT(hideListado()));
}

void MainWindow::hideListado() {
    disconnect(listado, SIGNAL(destroyed()), this, SLOT(hideListado()));
    listado = 0;
}

void MainWindow::showBarrio() {
    if (barrio == 0) {
        barrio = new BarrioForm;
        QMdiSubWindow *subWin = mdiArea->addSubWindow(barrio, Qt::SubWindow);
        subWin->setAttribute(Qt::WA_DeleteOnClose);
        barrio->setParent(subWin);
    }
    barrio->setWindowState(Qt::WindowMaximized);
    barrio->show();
    barrio->setFocus(Qt::ActiveWindowFocusReason);
    connect(barrio, SIGNAL(destroyed()), this, SLOT(hideBarrio()));
}

void MainWindow::hideBarrio() {
    disconnect(barrio, SIGNAL(destroyed()), this, SLOT(hideBarrio()));
    barrio = 0;
}

void MainWindow::showEncuesta() {
    if (encuesta == 0) {
        encuesta = new EncuestadorForm;
        QMdiSubWindow *subWin = mdiArea->addSubWindow(encuesta, Qt::SubWindow);
        subWin->setAttribute(Qt::WA_DeleteOnClose);
        encuesta->setParent(subWin);
    }
    encuesta->setWindowState(Qt::WindowMaximized);
    encuesta->show();
    encuesta->setFocus(Qt::ActiveWindowFocusReason);
    connect(encuesta, SIGNAL(destroyed()), this, SLOT(hideEncuesta()));
}

void MainWindow::hideEncuesta() {
    disconnect(encuesta, SIGNAL(destroyed()), this, SLOT(hideEncuesta()));
    encuesta = 0;
}

void MainWindow::showAbout() {
    about->show();
}

void MainWindow::showNuevo() {
    GeneralForm *generalForm;
    if (listado != 0)
        generalForm = new GeneralForm(this,listado->getModel());
   else
        generalForm = new GeneralForm(this);
    generalForm->show();
}

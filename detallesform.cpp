#include "detallesform.h"
#include "forms/commonform.hpp"
#include "forms/dimensionform.h"
#include "forms/edificacionform.h"
#include "forms/patiosform.h"
#include "forms/accesoform.h"
#include "forms/entornoform.h"
#include "forms/serviciosform.h"
#include <QtGui/QTreeWidgetItem>
#include <QtCore>

DetallesForm::DetallesForm(QWidget *parent, int cuenta) :
    QDialog(parent){
    setupUi(this);
    this->cuenta = cuenta;
    actualForm = new DimensionForm(cuenta, this);
    formArea->layout()->addWidget(actualForm);
    formTree->setCurrentItem(formTree->itemAt(0,0));
    formTree->expandAll();
    last = formTree->currentItem()->text(0);
}

void DetallesForm::closeEvent(QCloseEvent *event) {
    QDialog::closeEvent(event);
}

void DetallesForm::cambiarFormulario(QTreeWidgetItem *item, int column) {
    if (item->childCount() == 0 &&
        formTree->currentItem()->text(column) != last) {
        if (actualForm != 0) {
            actualForm->close();
            delete actualForm;
            actualForm = 0;
        }
        if (item->text(column) == "Dimensiones")
            actualForm = new DimensionForm(cuenta, this);
        if (item->text(column) == "Edificación")
            actualForm = new EdificacionForm(this);
        if (item->text(column) == "Patios")
            actualForm = new PatiosForm(cuenta, this);
        if (item->text(column) == "Acceso")
            actualForm = new AccesoForm(this);
        if (item->text(column) == "Entorno")
            actualForm = new EntornoForm(this);
        if (item->text(column) == "Nivel de Servicios")
            actualForm = new ServiciosForm(this);
        if (actualForm != 0)
            formArea->layout()->addWidget(actualForm);
        last = formTree->currentItem()->text(column);
    }
}

void DetallesForm::guardarActual() {
    if (actualForm != 0) {
        if (formTree->currentItem()->text(0) == "Dimensiones")
            ((DimensionForm*) actualForm)->guardar();
        if (formTree->currentItem()->text(0) == "Patios")
            ((PatiosForm*) actualForm)->guardar();
    }
}

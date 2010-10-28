#include "detallesform.h"
#include "forms/commonform.hpp"
#include "forms/dimensionform.h"
#include "forms/edificacionform.h"
#include <QtGui/QTreeWidgetItem>

DetallesForm::DetallesForm(QWidget *parent, int cuenta) :
    QDialog(parent){
    setupUi(this);
    this->cuenta = cuenta;
    actualForm = new DimensionForm(cuenta, this);
    formArea->layout()->addWidget(actualForm);
    formTree->setCurrentItem(formTree->itemAt(0,0));
    formTree->expandAll();
}

void DetallesForm::closeEvent(QCloseEvent *event) {
    QDialog::closeEvent(event);
}

void DetallesForm::cambiarFormulario(QTreeWidgetItem *item, int column) {
    if (item->childCount() == 0 &&
        formTree->currentItem()->text(column) != item->text(column)) {
        if (actualForm != 0) {
            actualForm->close();
            delete actualForm;
            actualForm = 0;
        }
        if (item->text(column) == "Dimensiones") {
            actualForm = new DimensionForm(cuenta, this);
            formArea->layout()->addWidget(actualForm);
        }
        if (item->text(column) == "Edificación") {
            actualForm = new EdificacionForm(this);
            formArea->layout()->addWidget(actualForm);
        }

    }
}

void DetallesForm::guardarActual() {
    ((CommonForm*) actualForm)->guardar();
}

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
    lastIdx = formTree->currentIndex().row();
}

void DetallesForm::closeEvent(QCloseEvent *event) {
    QDialog::closeEvent(event);
}

void DetallesForm::cambiarFormulario(QTreeWidgetItem *item, int column) {
    guardarActual();
    int idx = formTree->indexOfTopLevelItem(item);
    if (lastIdx == idx) {
        if (idx == DIMENSION)
            actualForm = new DimensionForm(cuenta, this);
        if (idx == EDIFICACION)
            actualForm = new EdificacionForm(this);
        if (idx == PATIOS)
            actualForm = new PatiosForm(cuenta, this);
        if (idx == ACCESO)
            actualForm = new AccesoForm(cuenta, this);
        if (idx == ENTORNO)
            actualForm = new EntornoForm(cuenta, this);
        if (idx == SERVICIOS)
            actualForm = new ServiciosForm(cuenta, this);
        if (actualForm != 0)
            formArea->layout()->addWidget(actualForm);
        connect(actualForm, SIGNAL(destroyed()), this, SLOT(cerrarForm()));
    }
    else
        formTree->setCurrentItem(formTree->itemAt(lastIdx,0));
}

void DetallesForm::guardarActual() {
    if (actualForm != 0) {
        bool close = (lastIdx != formTree->currentIndex().row());
        if (lastIdx == DIMENSION)
            static_cast<DimensionForm*>(actualForm)->guardar(close);
        if (lastIdx == PATIOS)
            static_cast<PatiosForm*>(actualForm)->guardar(close);
        if (lastIdx == ACCESO)
            static_cast<AccesoForm*>(actualForm)->guardar(close);
        if (lastIdx == SERVICIOS)
            static_cast<ServiciosForm*>(actualForm)->guardar(close);
    }
}

void DetallesForm::cerrarForm() {
    connect(actualForm, SIGNAL(destroyed()), this, SLOT(cerrarForm()));
    actualForm = 0;
    lastIdx = formTree->currentIndex().row();
}

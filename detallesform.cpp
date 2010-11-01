#include "detallesform.h"
#include "forms/dimensionform.h"
#include "forms/edificacionform.h"
#include "forms/patiosform.h"
#include "forms/accesoform.h"
#include "forms/entornoform.h"
#include "forms/serviciosform.h"
#include "forms/ocupacionform.h"
#include "forms/edadform.h"


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
    if (actualForm != 0) {
        actualForm->close();
        actualForm = 0;
    }
    int idx = formTree->indexOfTopLevelItem(item);
    if (idx == DIMENSION)
        actualForm = new DimensionForm(cuenta, this);
    if (idx == EDIFICACION)
        actualForm = new EdificacionForm(cuenta, this);
    if (idx == PATIOS)
        actualForm = new PatiosForm(cuenta, this);
    if (idx == ACCESO)
        actualForm = new AccesoForm(cuenta, this);
    if (idx == ENTORNO)
        actualForm = new EntornoForm(cuenta, this);
    if (idx == SERVICIOS)
        actualForm = new ServiciosForm(cuenta, this);
    if (idx == OCUPACION)
        actualForm = new OcupacionForm(cuenta, this);
    if (idx == EDAD)
        actualForm = new EdadForm(cuenta, this);
    if (actualForm != 0) {
        formArea->layout()->addWidget(actualForm);
    }
}

void DetallesForm::guardarActual() {
    if (actualForm != 0) {
        int idx = formTree->currentIndex().row();
        if (idx == DIMENSION)
            static_cast<DimensionForm*>(actualForm)->guardar();
        if (idx == EDIFICACION)
            static_cast<EdificacionForm*>(actualForm)->guardar();
        if (idx == PATIOS)
            static_cast<PatiosForm*>(actualForm)->guardar();
        if (idx == ACCESO)
            static_cast<AccesoForm*>(actualForm)->guardar();
        if (idx == SERVICIOS)
            static_cast<ServiciosForm*>(actualForm)->guardar();
        if (idx == OCUPACION)
            static_cast<OcupacionForm*>(actualForm)->guardar();
        if (idx == EDAD)
            static_cast<EdadForm*>(actualForm)->guardar();
        this->setFocus();
    }
}

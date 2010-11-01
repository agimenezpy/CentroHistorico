#include "detallesform.h"
#include "forms/dimensionform.h"
#include "forms/edificacionform.h"
#include "forms/patiosform.h"
#include "forms/accesoform.h"
#include "forms/entornoform.h"
#include "forms/serviciosform.h"
#include "forms/ocupacionform.h"
#include "forms/edadform.h"
#include "forms/conservacionform.h"
#include "forms/valoracionform.h"
#include <QTreeWidgetItem>
#include <QDebug>


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
    if (item->childCount() == 0) {
        if (actualForm != 0) {
            actualForm->close();
            actualForm = 0;
        }
        int idx;
        int parent = formTree->indexOfTopLevelItem(item->parent());
        if (parent != -1)
            idx = parent*10 + item->parent()->indexOfChild(item);
        else
            idx = formTree->indexOfTopLevelItem(item);
        switch (idx) {
            case DIMENSION:
                actualForm = new DimensionForm(cuenta, this);
                break;
            case EDIFICACION:
                actualForm = new EdificacionForm(cuenta, this);
                break;
            case PATIOS:
                actualForm = new PatiosForm(cuenta, this);
                break;
            case ACCESO:
                actualForm = new AccesoForm(cuenta, this);
                break;
            case ENTORNO:
                actualForm = new EntornoForm(cuenta, this);
                break;
            case SERVICIOS:
                actualForm = new ServiciosForm(cuenta, this);
                break;
            case OCUPACION:
                actualForm = new OcupacionForm(cuenta, this);
                break;
            case EDAD:
                actualForm = new EdadForm(cuenta, this);
                break;
            case CONSERVACION:
                actualForm = new ConservacionForm(cuenta, this);
                break;
            case VALORACION:
                actualForm = new ValoracionForm(cuenta, this);
                break;
        }
        if (actualForm != 0) {
            formArea->layout()->addWidget(actualForm);
        }
    }
}

void DetallesForm::guardarActual() {
    if (actualForm != 0 && formTree->currentItem()->childCount() == 0) {
        int idx;
        QTreeWidgetItem *item = formTree->currentItem();
        int parent = formTree->indexOfTopLevelItem(item->parent());
        if (parent != -1)
            idx = parent*10 + item->parent()->indexOfChild(item);
        else
            idx = formTree->currentIndex().row();
        switch (idx) {
            case DIMENSION:
                static_cast<DimensionForm*>(actualForm)->guardar();
                break;
            case EDIFICACION:
                static_cast<EdificacionForm*>(actualForm)->guardar();
                break;
            case PATIOS:
                static_cast<PatiosForm*>(actualForm)->guardar();
                break;
            case ACCESO:
                static_cast<AccesoForm*>(actualForm)->guardar();
                break;
            case SERVICIOS:
                static_cast<ServiciosForm*>(actualForm)->guardar();
                break;
            case OCUPACION:
                static_cast<OcupacionForm*>(actualForm)->guardar();
                break;
            case EDAD:
                static_cast<EdadForm*>(actualForm)->guardar();
                break;
            case CONSERVACION:
                static_cast<ConservacionForm*>(actualForm)->guardar();
                break;
            case VALORACION:
                static_cast<ValoracionForm*>(actualForm)->guardar();
                break;
        }
    }
}

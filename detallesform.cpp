#include "detallesform.h"
#include "forms/dimensionform.h"
#include "forms/edificacionform.h"
#include "forms/patiosform.h"
#include "forms/accesoform.h"
#include "forms/entornoform.h"
#include "forms/serviciosform.h"
#include "forms/ocupacionform.h"
#include "forms/edadform.h"
#include "forms/tratamientoform.h"
#include "forms/fachadaform.h"
#include "forms/rematesform.h"
#include "forms/cubiertaform.h"
#include "forms/estructuraform.h"
#include "forms/patologiaform.h"
#include "forms/conservacionform.h"
#include "forms/valoracionform.h"
#include "forms/fotosform.h"
#include <QTreeWidgetItem>


DetallesForm::DetallesForm(QWidget *parent, int cuenta) :
    QDialog(parent){
    setupUi(this);
    this->cuenta = cuenta;
    actualForm = new DimensionForm(cuenta, this);
    formArea->layout()->addWidget(actualForm);
    formTree->setCurrentItem(formTree->itemAt(0,0));
    formTree->expandAll();
}

void DetallesForm::cambiarFormulario(QTreeWidgetItem *item, int /*column*/) {
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
            case TRATAMIENTO:
                actualForm = new TratamientoForm(cuenta, this);
                break;
            case FACHADA:
                actualForm = new FachadaForm(cuenta, this);
                break;
            case REMATES:
                actualForm = new RematesForm(cuenta, this);
                break;
            case CUBIERTA:
                actualForm = new CubiertaForm(cuenta, this);
                break;
            case ESTRUCTURA:
                actualForm = new EstructuraForm(cuenta, this);
                break;
            case PATOLOGIAS:
                actualForm = new PatologiaForm(cuenta, this);
                break;
            case CONSERVACION:
                actualForm = new ConservacionForm(cuenta, this);
                break;
            case VALORACION:
                actualForm = new ValoracionForm(cuenta, this);
                break;
            case FOTOS:
                actualForm = new FotosForm(cuenta, this);
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
            case ENTORNO:
                static_cast<EntornoForm*>(actualForm)->guardar();
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
            case TRATAMIENTO:
                static_cast<TratamientoForm*>(actualForm)->guardar();
                break;
            case FACHADA:
                static_cast<FachadaForm*>(actualForm)->guardar();
                break;
            case REMATES:
                static_cast<RematesForm*>(actualForm)->guardar();
                break;
            case CUBIERTA:
                static_cast<CubiertaForm*>(actualForm)->guardar();
                break;
            case ESTRUCTURA:
                static_cast<EstructuraForm*>(actualForm)->guardar();
                break;
            case PATOLOGIAS:
                static_cast<PatologiaForm*>(actualForm)->guardar();
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

void DetallesForm::siguiente() {
    QTreeWidgetItem *item = formTree->itemBelow(formTree->currentItem());
    if (item != 0) {
        while (item->childCount() > 0)
            item = formTree->itemBelow(item);
        formTree->setCurrentItem(item);
    }
    else
        formTree->setCurrentItem(formTree->topLevelItem(DIMENSION));
    cambiarFormulario(formTree->currentItem(), 0);
}

void DetallesForm::anterior() {
    QTreeWidgetItem *item = formTree->itemAbove(formTree->currentItem());
    if (item != 0) {
        while (item->childCount() > 0)
            item = formTree->itemAbove(item);
        formTree->setCurrentItem(item);
    }
    else
        formTree->setCurrentItem(formTree->topLevelItem(FOTOS));
    cambiarFormulario(formTree->currentItem(), 0);
}

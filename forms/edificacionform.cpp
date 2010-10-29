#include "edificacionform.h"

EdificacionForm::EdificacionForm(QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    QIntValidator *val = new QIntValidator(this);
    val->setRange(1,4);
    edifPisosEdit->setValidator(val);
    QDoubleValidator* val2 = new QDoubleValidator(this);
    val2->setBottom(0);
    edifSuperficieEdit->setValidator(val2);
    edifTotSuperficieEdit->setValidator(val2);
}

void EdificacionForm::modificarEdificacion(QString textChanged) {
    int pos = 0;
    if (textChanged.size() > 0) {
        pos = textChanged.toInt();
    }
    for (int j = 0; j <= edificacionTable->columnCount(); j++) {
        if (j < pos)
            edificacionTable->showColumn(j);
        else
            edificacionTable->hideColumn(j);
    }
}

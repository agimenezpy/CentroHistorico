#include "edificacionform.h"

EdificacionForm::EdificacionForm(QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
}

void EdificacionForm::modificarEdificacion(QString textChanged) {
    QIntValidator *val = new QIntValidator(this);
    val->setRange(1,4);
    int pos = 0;
    if (textChanged.size() > 0 &&
        val->validate(textChanged, pos) == QValidator::Acceptable) {
        pos = textChanged.toInt();
    }
    for (int j = 0; j <= edificacionTable->columnCount(); j++) {
        if (j < pos)
            edificacionTable->showColumn(j);
        else
            edificacionTable->hideColumn(j);
    }
    delete val;
}

bool EdificacionForm::commit() {
    return false;
}

bool EdificacionForm::revert() {
    return false;
}

bool EdificacionForm::valido() {
    return false;
}

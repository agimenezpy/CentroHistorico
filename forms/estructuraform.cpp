#include "estructuraform.h"
#include <QDataWidgetMapper>

EstructuraForm::EstructuraForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
    construct(this,"estructura",cuentaEdit->text());
    mapper->addMapping(cuentaEdit, 0);
    mapper->addMapping(estPisoEdit, 1);
    mapper->addMapping(estMurosEdit, 2);
    mapper->addMapping(estPilaresEdit, 3);
    mapper->addMapping(estVigasEdit, 4);
    mapper->addMapping(estArcosEdit, 5);
    mapper->addMapping(estEscaleraEdit, 6);
    init();
}

void EstructuraForm::guardar() {
    this->submit();
}

#include "rematesform.h"
#include <QDataWidgetMapper>

RematesForm::RematesForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    cuentaEdit->setVisible(false);
    cuentaEdit->setText(QString("%1").arg(cuenta));
    construct(this,"remates",cuentaEdit->text());
    mapper->addMapping(cuentaEdit, 0);
    mapper->addMapping(remAleroCheck, 1);
    mapper->addMapping(remCornisaCheck, 2);
    mapper->addMapping(remAntepechoCheck, 3);
    mapper->addMapping(remBalaustradaCheck, 4);
    mapper->addMapping(remOtrosEdit, 5);
    init();
}

void RematesForm::guardar() {
    this->submit();
}

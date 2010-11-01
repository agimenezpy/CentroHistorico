#include "dimensionform.h"
#include <QDataWidgetMapper>
#include <QDoubleValidator>

DimensionForm::DimensionForm(int cuenta, QWidget *parent) :
    QGroupBox(parent) {
    setupUi(this);
    QString ccc = QString("%1").arg(cuenta);
    cuentaEdit->setText(ccc);
    cuentaEdit->setVisible(false);
    construct(this, QString("dimension"), ccc);
    mapper->addMapping(cuentaEdit, 0);
    mapper->addMapping(loteAnchoEdit, 1);
    mapper->addMapping(loteLargoEdit, 2);
    mapper->addMapping(loteSuperficieEdit, 3);
    mapper->addMapping(loteOcupacionEdit, 4);
    mapper->addMapping(loteEdificabilidadEdit, 5);
    init();
    QDoubleValidator *val = new QDoubleValidator(this);
    val->setBottom(0);
    loteAnchoEdit->setValidator(val);
    loteLargoEdit->setValidator(val);
    loteSuperficieEdit->setValidator(val);
    loteOcupacionEdit->setValidator(val);
    loteEdificabilidadEdit->setValidator(val);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void DimensionForm::closeEvent(QCloseEvent *event) {
    QGroupBox::closeEvent(event);
}

void DimensionForm::guardar() {
    this->submit();
}

#include "patiosform.h"
#include "util/combodelegate.h"
#include <QDataWidgetMapper>
#include <QtCore>

PatiosForm::PatiosForm(int cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    QString ccc = QString("%1").arg(cuenta);
    cuentaEdit->setText(ccc);
    cuentaEdit->setVisible(false);
    construct(this, "patio", ccc);
    mapper->setItemDelegate(new ComboDelegate(this));
    mapper->addMapping(cuentaEdit, 0);
    mapper->addMapping(patioEstacionamientoEdit, 1);
    mapper->addMapping(patioOcupacionCmb, 2);
    mapper->addMapping(patioJardinCheck, 3);
    mapper->addMapping(patioComercioCheck, 4);
    mapper->addMapping(patioAbandonadoCheck, 5);
    mapper->addMapping(patioOtrosCheck, 6);
    init();
    QDoubleValidator *val = new QDoubleValidator(this);
    val->setBottom(0);
    patioEstacionamientoEdit->setValidator(val);
    patioOcupacionCmb->addItem("Temporal",QChar('T'));
    patioOcupacionCmb->addItem("Permanente",QChar('P'));
}

void PatiosForm::guardar() {
    this->submit();
}

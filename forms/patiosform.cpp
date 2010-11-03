#include "patiosform.h"
#include "util/combodelegate.h"
#include <QDataWidgetMapper>
#include <QDoubleValidator>

PatiosForm::PatiosForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    patioOcupacionCmb->setItemData(0,QChar('\0'));
    patioOcupacionCmb->addItem("Temporal",QChar('T'));
    patioOcupacionCmb->addItem("Permanente",QChar('P'));
    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
    construct(this, "patio", cuentaEdit->text());
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
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void PatiosForm::guardar() {
    this->submit();
}

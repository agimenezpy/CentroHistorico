#include "ocupacionform.h"
#include "util/combodelegate.h"
#include <QDataWidgetMapper>
#include <QIntValidator>

OcupacionForm::OcupacionForm(int cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    ocupTenenciaCmb->setItemData(0,QChar('\0'));
    ocupTenenciaCmb->addItem("En propiedad",QChar('P'));
    ocupTenenciaCmb->addItem("En alquiler",QChar('A'));

    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
    construct(this,"ocupacion",cuentaEdit->text());
    mapper->addMapping(cuentaEdit, 0);
    mapper->addMapping(ocupCantFamiliasEdit, 1);
    mapper->addMapping(ocupTenenciaCmb, 2);
    mapper->addMapping(ocupMantenimientoCheck, 3);
    mapper->setItemDelegate(new ComboDelegate(this));
    init();
    QIntValidator *val = new QIntValidator(this);
    val->setBottom(0);
    ocupCantFamiliasEdit->setValidator(val);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void OcupacionForm::guardar() {
    this->submit();
}


#include "edadform.h"
#include "util/combodelegate.h"
#include <QDataWidgetMapper>
#include <QIntValidator>

EdadForm::EdadForm(int cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    edadAnyoCmb->setItemData(0,QChar('\0'));
    edadAnyoCmb->addItem("Hasta 1800",QChar('A'));
    edadAnyoCmb->addItem("1800 - 1850",QChar('B'));
    edadAnyoCmb->addItem("1850 - 1870",QChar('C'));
    edadAnyoCmb->addItem("1870 - 1900",QChar('D'));

    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
    construct(this,"edad",cuentaEdit->text());
    mapper->addMapping(cuentaEdit, 0);
    mapper->addMapping(edadAnyoEdit, 1);
    mapper->addMapping(edadAnyoCmb, 2);
    mapper->setItemDelegate(new ComboDelegate(this));
    init();
    QIntValidator *val = new QIntValidator(this);
    edadAnyoEdit->setValidator(val);
}

void EdadForm::guardar() {
    this->submit();
}

void EdadForm::cambio(int index) {
    if (index != 0) {
        edadAnyoEdit->setEnabled(true);
        edadAnyoEdit->setText("");
    }
    else {
        edadAnyoEdit->setEnabled(false);
        edadAnyoEdit->setFocus();
    }
}

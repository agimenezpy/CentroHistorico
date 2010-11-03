#include "conservacionform.h"
#include "util/combodelegate.h"
#include <QDataWidgetMapper>

ConservacionForm::ConservacionForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    consEstadoCmb->setItemData(0, QChar('\0'));
    consEstadoCmb->addItem("Bueno (> 70%)", QChar('B'));
    consEstadoCmb->addItem("Regular (> 30% y < 70%)", QChar('E'));
    consEstadoCmb->addItem("Malo (< 30%)", QChar('M'));
    consEstadoCmb->addItem("Ruina", QChar('R'));
    consObraCmb->setItemData(0, QChar('\0'));
    consObraCmb->addItem("En marcha", QChar('M'));
    consObraCmb->addItem("Interrumpida", QChar('I'));
    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
    construct(this,"conservacion",cuentaEdit->text());
    mapper->addMapping(cuentaEdit, 0);
    mapper->addMapping(consUsoEdit, 1);
    mapper->addMapping(consReconvertidaEdit, 2);
    mapper->addMapping(consObraCmb, 3);
    mapper->addMapping(consEstadoCmb, 4);
    mapper->setItemDelegate(new ComboDelegate(this));
    init();
}

void ConservacionForm::guardar() {
    this->submit();
}

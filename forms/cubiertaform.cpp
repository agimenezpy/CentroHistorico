#include "cubiertaform.h"
#include "util/combodelegate.h"
#include <QDataWidgetMapper>

CubiertaForm::CubiertaForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    cubTipoCmb->addItem("Horizontal", QChar('H'));
    cubTipoCmb->addItem("Inclinada", QChar('I'));
    cubIncCmb->setItemData(0, QChar('\0'));
    cubIncCmb->addItem("Teja", QChar('T'));
    cubIncCmb->addItem("Zinc", QChar('Z'));
    cubIncCmb->addItem("Asb", QChar('A'));
    cubIncCmb->setEnabled(false);
    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
    construct(this,"cubierta",cuentaEdit->text());
    mapper->addMapping(cuentaEdit, 0);
    mapper->addMapping(cubTipoCmb, 1);
    mapper->addMapping(cubIncCmb, 2);
    mapper->setItemDelegate(new ComboDelegate(this));
    init();
    establecerInclinada(cubTipoCmb->currentIndex());
}

void CubiertaForm::guardar() {
    this->submit();
}

void CubiertaForm::establecerInclinada(int index) {
    if (index != 2) {
        cubIncCmb->setCurrentIndex(0);
        cubIncCmb->setEnabled(false);
    }
    else
        cubIncCmb->setEnabled(true);
}

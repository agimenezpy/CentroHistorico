#include "cubiertaform.h"
#include "util/combodelegate.h"
#include <QDataWidgetMapper>

CubiertaForm::CubiertaForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    cubTipoCmb->addItem("Horizontal", QChar('H'));
    cubTipoCmb->addItem("Inclinada", QChar('I'));
    cubTejaCheck->setEnabled(false);
    cubZincCheck->setEnabled(false);
    cubAsbCheck->setEnabled(false);
    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
    construct(this,"cubierta",cuentaEdit->text());
    mapper->addMapping(cuentaEdit, 0);
    mapper->addMapping(cubTipoCmb, 1);
    mapper->addMapping(cubTejaCheck, 2);
    mapper->addMapping(cubZincCheck, 3);
    mapper->addMapping(cubAsbCheck, 4);
    mapper->setItemDelegate(new ComboDelegate(this));
    init();
    establecerInclinada(cubTipoCmb->currentIndex());
}

void CubiertaForm::guardar() {
    this->submit();
}

void CubiertaForm::establecerInclinada(int index) {
    bool en = true;
    if (index != 2) {
        en = false;
        cubTejaCheck->setChecked(en);
        cubZincCheck->setChecked(en);
        cubAsbCheck->setChecked(en);
    }
    cubTejaCheck->setEnabled(en);
    cubZincCheck->setEnabled(en);
    cubAsbCheck->setEnabled(en);
}

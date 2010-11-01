#include "accesoform.h"
#include "util/combodelegate.h"
#include <QDataWidgetMapper>

AccesoForm::AccesoForm(int cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    accesoNivelCmb->setItemData(0,QChar('\0'));
    accesoNivelCmb->addItem("Enrasado",QChar('E'));
    accesoNivelCmb->addItem("Bajo",QChar('B'));
    accesoNivelCmb->addItem("Alto",QChar('A'));

    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
    construct(this,"acceso",cuentaEdit->text());
    mapper->setItemDelegate(new ComboDelegate(this));
    mapper->addMapping(cuentaEdit, 0);
    mapper->addMapping(accesoNivelCmb, 1);
    mapper->addMapping(accesoCentralCheck, 2);
    mapper->addMapping(accesoLatIzqCheck, 3);
    mapper->addMapping(accesoLatDerCheck, 4);
    mapper->addMapping(accesoEsquinaCheck, 5);
    mapper->addMapping(accesoGaleriaCheck, 6);
    mapper->addMapping(accesoModificadoCheck, 7);
    init();
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void AccesoForm::guardar() {
    this->submit();
}

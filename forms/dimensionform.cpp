#include "dimensionform.h"
#include <QtSql>
#include <QDataWidgetMapper>
#include <QtGui/QMessageBox>

DimensionForm::DimensionForm(int cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    construct(this,"dimension",QString("%1").arg(cuenta));
    mapper->addMapping(loteAnchoEdit, 1);
    mapper->addMapping(loteLargoEdit, 2);
    mapper->addMapping(loteSuperficieEdit, 3);
    mapper->addMapping(loteOcupacionEdit, 4);
    mapper->addMapping(loteOcupacionEdit, 5);
    init();
    model->record().setValue("cuenta",QVariant(cuenta));
}

void DimensionForm::closeEvent(QCloseEvent *event) {
    int confirm = QMessageBox::question(this,"Guardar Cambios","¿Desea guardar los cambios?","Si", "No");
    if (confirm == 0) {
        qDebug() << "yes" << confirm;
    }
    else if (confirm == 1)
        qDebug() << "no" << confirm;
    else
        qDebug() << confirm;
    QGroupBox::closeEvent(event);
}

void DimensionForm::guardar() {
    this->submit();
}

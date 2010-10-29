#include "serviciosform.h"
#include "util/combodelegate.h"
#include <QDataWidgetMapper>

ServiciosForm::ServiciosForm(int cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    cuentaEdit->setText(QString("%1").arg(cuenta));
    construct(this, "servicio", cuentaEdit->text());
    mapper->setItemDelegate(new ComboDelegate(this));
    mapper->addMapping(cuentaEdit, 0);
    mapper->addMapping(servAguaCmb, 1);
    mapper->addMapping(servDesagueCmb, 2);
    mapper->addMapping(servHigieneCmb, 3);
    mapper->addMapping(servLavanderiasCmb, 4);
    mapper->addMapping(servLuzCmb, 5);
    mapper->addMapping(servTransporteCheck, 6);
    mapper->addMapping(servEstudiosCmb, 7);
    mapper->addMapping(servRecreoCmb, 8);
    mapper->addMapping(servBarrioCmb, 9);
    mapper->addMapping(servCambioCmb, 10);
    init();
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void ServiciosForm::guardar(bool close) {
    if (this->submit() && close)
        this->close();
}

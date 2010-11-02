#include "serviciosform.h"
#include "util/combodelegate.h"
#include <QDataWidgetMapper>

ServiciosForm::ServiciosForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    servAguaCmb->setItemData(0,QChar('\0'));
    servAguaCmb->addItem("Siempre",QChar('S'));
    servAguaCmb->addItem("Por horas",QChar('H'));
    servAguaCmb->addItem("De repente",QChar('R'));
    servDesagueCmb->setItemData(0,QChar('\0'));
    servDesagueCmb->addItem("Normal",QChar('N'));
    servDesagueCmb->addItem("Se Tapa",QChar('T'));
    servDesagueCmb->addItem("Sin sifón",QChar('S'));
    servHigieneCmb->setItemData(0,QChar('\0'));
    servHigieneCmb->addItem("Privados",QChar('P'));
    servHigieneCmb->addItem("Comunal",QChar('C'));
    servHigieneCmb->addItem("No tiene",QChar('N'));
    servLavanderiasCmb->setItemData(0,QChar('\0'));
    servLavanderiasCmb->addItem("Privados",QChar('P'));
    servLavanderiasCmb->addItem("Comunal",QChar('C'));
    servLavanderiasCmb->addItem("No tiene",QChar('N'));
    servLuzCmb->setItemData(0,QChar('\0'));
    servLuzCmb->addItem("Normal",QChar('O'));
    servLuzCmb->addItem("Baja tensión",QChar('B'));
    servLuzCmb->addItem("No Tiene",QChar('N'));
    servEstudiosCmb->setItemData(0,QChar('\0'));
    servEstudiosCmb->addItem("Barrio",QChar('B'));
    servEstudiosCmb->addItem("Fuera CH",QChar('F'));
    servRecreoCmb->setItemData(0,QChar('\0'));
    servRecreoCmb->addItem("Barrio",QChar('B'));
    servRecreoCmb->addItem("Fuera CH",QChar('F'));
    servBarrioCmb->setItemData(0,QChar('\0'));
    servBarrioCmb->addItem("Si",QChar('S'));
    servBarrioCmb->addItem("Medianamente",QChar('M'));
    servBarrioCmb->addItem("No",QChar('N'));
    servCambioCmb->setItemData(0,QChar('\0'));
    servCambioCmb->addItem("Barrio",QChar('B'));
    servCambioCmb->addItem("Fuera CH",QChar('F'));

    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
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

void ServiciosForm::guardar() {
    this->submit();
}

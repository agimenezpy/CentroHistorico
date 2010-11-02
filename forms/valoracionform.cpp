#include "valoracionform.h"
#include "util/combodelegate.h"
#include <QDataWidgetMapper>
#include <QCompleter>

ValoracionForm::ValoracionForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    valCalificacionCmb->setItemData(0, QChar('\0'));
    valCalificacionCmb->addItem("Monumental", QChar('M'));
    valCalificacionCmb->addItem("Valor Arquitectónico", QChar('A'));
    valCalificacionCmb->addItem("Valor Ambiental", QChar('B'));
    valCalificacionCmb->addItem("Neutro o Integrado", QChar('I'));
    valCalificacionCmb->addItem("Negativo", QChar('N'));

    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
    construct(this, "valoracion", cuentaEdit->text());
    mapper->addMapping(cuentaEdit, 0);
    mapper->addMapping(valEstiloEdit, 1);
    mapper->addMapping(valCalificacionCmb, 2);
    mapper->setItemDelegate(new ComboDelegate(this));
    init();
    QStringList estilos;
    estilos << "Colonial"
            << "Neoclásico"
            << "Neoclásico Francés"
            << "Neoclásico Italianizado"
            << "Neoclásico Catalán"
            << "Neoclásico Moderno"
            << "Posmoderno"
            << "Plateresco"
            << "Art Deco"
            << "Neogótico";
    QCompleter *comp = new QCompleter(estilos,this);
    comp->setCaseSensitivity(Qt::CaseInsensitive);
    valEstiloEdit->setCompleter(comp);
}

void ValoracionForm::guardar() {
    this->submit();
}

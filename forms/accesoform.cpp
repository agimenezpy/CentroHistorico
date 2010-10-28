#include "accesoform.h"

AccesoForm::AccesoForm(QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
}

void AccesoForm::changeEvent(QEvent *e)
{
    QGroupBox::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

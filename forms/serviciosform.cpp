#include "serviciosform.h"

ServiciosForm::ServiciosForm(QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
}

void ServiciosForm::changeEvent(QEvent *e)
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

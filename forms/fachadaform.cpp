#include "fachadaform.h"

FachadaForm::FachadaForm(QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
}

void FachadaForm::changeEvent(QEvent *e)
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

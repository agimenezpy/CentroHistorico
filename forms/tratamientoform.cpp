#include "tratamientoform.h"

TratamientoForm::TratamientoForm(QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
}

void TratamientoForm::changeEvent(QEvent *e)
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

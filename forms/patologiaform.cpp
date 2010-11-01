#include "patologiaform.h"

PatologiaForm::PatologiaForm(QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
}

void PatologiaForm::changeEvent(QEvent *e)
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

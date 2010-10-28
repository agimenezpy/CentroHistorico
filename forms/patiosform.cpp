#include "patiosform.h"

PatiosForm::PatiosForm(QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
}

void PatiosForm::changeEvent(QEvent *e)
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

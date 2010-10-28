#include "entornoform.h"

EntornoForm::EntornoForm(QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
}

void EntornoForm::changeEvent(QEvent *e)
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

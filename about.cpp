#include "about.h"

About::About(QWidget *parent) :
    QDialog(parent){
    setupUi(this);
    QString vers(qVersion());
    version->setText("Basado en Qt " + vers);
    this->setVisible(false);
}

void About::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

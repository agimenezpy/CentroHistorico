#include "fotosform.h"
#include "ui_fotosform.h"

FotosForm::FotosForm(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::FotosForm)
{
    ui->setupUi(this);
}

FotosForm::~FotosForm()
{
    delete ui;
}

void FotosForm::changeEvent(QEvent *e)
{
    QGroupBox::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

#ifndef FACHADAFORM_H
#define FACHADAFORM_H

#include "ui_fachadaform.h"

class FachadaForm : public QGroupBox, private Ui::FachadaForm {
    Q_OBJECT
public:
    FachadaForm(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
};

#endif // FACHADAFORM_H

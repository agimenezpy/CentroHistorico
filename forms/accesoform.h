#ifndef ACCESOFORM_H
#define ACCESOFORM_H

#include "ui_accesoform.h"

class AccesoForm : public QGroupBox, private Ui::AccesoForm {
    Q_OBJECT
public:
    AccesoForm(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
};

#endif // ACCESOFORM_H

#ifndef ACCESOFORM_H
#define ACCESOFORM_H

#include "ui_accesoform.h"
#include "modelhelper.hpp"

class AccesoForm : public QGroupBox, public ModelHelper, private Ui::AccesoForm {
    Q_OBJECT
public:
    AccesoForm(int cuenta, QWidget *parent = 0);
    void guardar(bool close = false);

};

#endif // ACCESOFORM_H

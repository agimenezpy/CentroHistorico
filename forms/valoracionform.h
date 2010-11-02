#ifndef VALORACIONFORM_H
#define VALORACIONFORM_H

#include "ui_valoracionform.h"
#include "modelhelper.hpp"

class ValoracionForm : public QGroupBox, public ModelHelper, private Ui::ValoracionForm {
    Q_OBJECT
public:
    ValoracionForm(const int &cuenta, QWidget *parent = 0);
    void guardar();

};

#endif // VALORACIONFORM_H

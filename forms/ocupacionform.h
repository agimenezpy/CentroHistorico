#ifndef OCUPACIONFORM_H
#define OCUPACIONFORM_H

#include "ui_ocupacionform.h"
#include "modelhelper.hpp"

class OcupacionForm : public QGroupBox, public ModelHelper, private Ui::OcupacionForm {
    Q_OBJECT
public:
    OcupacionForm(const int &cuenta, QWidget *parent = 0);
    void guardar();

};

#endif // OCUPACIONFORM_H

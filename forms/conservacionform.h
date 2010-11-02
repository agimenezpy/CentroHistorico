#ifndef CONSERVACIONFORM_H
#define CONSERVACIONFORM_H

#include "ui_conservacionform.h"
#include "modelhelper.hpp"

class ConservacionForm : public QGroupBox, public ModelHelper, private Ui::ConservacionForm {
    Q_OBJECT
public:
    ConservacionForm(const int &cuenta, QWidget *parent = 0);
    void guardar();
};

#endif // CONSERVACIONFORM_H

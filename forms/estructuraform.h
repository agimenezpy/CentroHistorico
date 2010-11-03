#ifndef ESTRUCTURAFORM_H
#define ESTRUCTURAFORM_H

#include "ui_estructuraform.h"
#include "modelhelper.hpp"

class EstructuraForm : public QGroupBox, public ModelHelper, private Ui::EstructuraForm {
    Q_OBJECT
public:
    EstructuraForm(const int &cuenta, QWidget *parent = 0);
    void guardar();
};

#endif // ESTRUCTURAFORM_H

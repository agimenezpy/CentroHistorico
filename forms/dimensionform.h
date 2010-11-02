#ifndef DIMENSIONFORM_H
#define DIMENSIONFORM_H

#include "ui_dimensionform.h"
#include "modelhelper.hpp"

class DimensionForm : public QGroupBox, public ModelHelper, private Ui::DimensionForm {
    Q_OBJECT
public:
    DimensionForm(const int &cuenta, QWidget *parent = 0);
    void guardar();

};

#endif // DIMENSIONFORM_H

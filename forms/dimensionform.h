#ifndef DIMENSIONFORM_H
#define DIMENSIONFORM_H

#include "ui_dimensionform.h"
#include "commonform.hpp"
#include "modelhelper.hpp"

class DimensionForm : public QGroupBox, public ModelHelper, public CommonForm, private Ui::DimensionForm {
    Q_OBJECT
public:
    DimensionForm(int cuenta, QWidget *parent = 0);
    void guardar();

protected:
    void closeEvent(QCloseEvent *event);

};

#endif // DIMENSIONFORM_H

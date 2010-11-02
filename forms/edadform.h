#ifndef EDADFORM_H
#define EDADFORM_H

#include "ui_edadform.h"
#include "modelhelper.hpp"

class EdadForm : public QGroupBox, public ModelHelper, private Ui::EdadForm {
    Q_OBJECT
public:
    EdadForm(const int &cuenta, QWidget *parent = 0);
    void guardar();

private slots:
    void cambio(int index);
};

#endif // EDADFORM_H

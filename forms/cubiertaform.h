#ifndef CUBIERTAFORM_H
#define CUBIERTAFORM_H

#include "ui_cubiertaform.h"
#include "modelhelper.hpp"

class CubiertaForm : public QGroupBox, public ModelHelper, private Ui::CubiertaForm {
    Q_OBJECT
public:
    CubiertaForm(const int &cuenta, QWidget *parent = 0);
    void guardar();

private slots:
    void establecerInclinada(int index);
};

#endif // CUBIERTAFORM_H

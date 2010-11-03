#ifndef EDIFICACIONFORM_H
#define EDIFICACIONFORM_H

#include "ui_edificacionform.h"
#include "modelhelper.hpp"

class EdificacionForm : public QGroupBox, public ModelHelper, private Ui::EdificacionForm {
    Q_OBJECT
public:
    EdificacionForm(const int &cuenta, QWidget *parent = 0);
    void guardar();

protected slots:
    void modificarEdificacion(QString textChanged);

private:
    QTableWidgetItem *createTableItem();
    void setUsoSuelo();
    int exist;
};

#endif // EDIFICACIONFORM_H

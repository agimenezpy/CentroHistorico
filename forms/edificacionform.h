#ifndef EDIFICACIONFORM_H
#define EDIFICACIONFORM_H

#include "ui_edificacionform.h"

class EdificacionForm : public QGroupBox, private Ui::EdificacionForm {
    Q_OBJECT
public:
    EdificacionForm(QWidget *parent = 0);
    bool valido();
    bool commit();
    bool revert();

protected slots:
    void modificarEdificacion(QString textChanged);

};

#endif // EDIFICACIONFORM_H

#ifndef SERVICIOSFORM_H
#define SERVICIOSFORM_H

#include "ui_serviciosform.h"
#include "modelhelper.hpp"

class ServiciosForm : public QGroupBox, public ModelHelper, private Ui::ServiciosForm {
    Q_OBJECT
public:
    ServiciosForm(int cuenta, QWidget *parent = 0);
    void guardar(bool close = false);

};

#endif // SERVICIOSFORM_H

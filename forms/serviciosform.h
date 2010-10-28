#ifndef SERVICIOSFORM_H
#define SERVICIOSFORM_H

#include "ui_serviciosform.h"

class ServiciosForm : public QGroupBox, private Ui::ServiciosForm {
    Q_OBJECT
public:
    ServiciosForm(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
};

#endif // SERVICIOSFORM_H

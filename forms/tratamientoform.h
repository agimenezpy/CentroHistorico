#ifndef TRATAMIENTOFORM_H
#define TRATAMIENTOFORM_H

#include "ui_tratamientoform.h"

class TratamientoForm : public QGroupBox, private Ui::TratamientoForm {
    Q_OBJECT
public:
    TratamientoForm(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
};

#endif // TRATAMIENTOFORM_H

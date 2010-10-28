#ifndef ENTORNOFORM_H
#define ENTORNOFORM_H

#include "ui_entornoform.h"

class EntornoForm : public QGroupBox, private Ui::EntornoForm {
    Q_OBJECT
public:
    EntornoForm(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
};

#endif // ENTORNOFORM_H

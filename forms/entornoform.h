#ifndef ENTORNOFORM_H
#define ENTORNOFORM_H

#include "ui_entornoform.h"

class EntornoForm : public QGroupBox, private Ui::EntornoForm {
    Q_OBJECT
public:
    EntornoForm(const int &cuenta, QWidget *parent = 0);

};

#endif // ENTORNOFORM_H

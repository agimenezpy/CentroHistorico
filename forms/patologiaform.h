#ifndef PATOLOGIAFORM_H
#define PATOLOGIAFORM_H

#include "ui_patologiaform.h"

class PatologiaForm : public QGroupBox, private Ui::PatologiaForm {
    Q_OBJECT
public:
    PatologiaForm(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
};

#endif // PATOLOGIAFORM_H

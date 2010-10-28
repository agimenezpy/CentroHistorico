#ifndef PATIOSFORM_H
#define PATIOSFORM_H

#include "ui_patiosform.h"

class PatiosForm : public QGroupBox, private Ui::PatiosForm {
    Q_OBJECT
public:
    PatiosForm(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
};

#endif // PATIOSFORM_H

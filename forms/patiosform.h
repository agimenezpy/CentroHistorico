#ifndef PATIOSFORM_H
#define PATIOSFORM_H

#include "ui_patiosform.h"
#include "modelhelper.hpp"

class PatiosForm : public QGroupBox, public ModelHelper, private Ui::PatiosForm {
    Q_OBJECT
public:
    PatiosForm(int cuenta, QWidget *parent = 0);
    void guardar(bool close = false);
private:
    
};

#endif // PATIOSFORM_H

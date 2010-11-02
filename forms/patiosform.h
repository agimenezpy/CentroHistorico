#ifndef PATIOSFORM_H
#define PATIOSFORM_H

#include "ui_patiosform.h"
#include "modelhelper.hpp"

class PatiosForm : public QGroupBox, public ModelHelper, private Ui::PatiosForm {
    Q_OBJECT
public:
    PatiosForm(const int &cuenta, QWidget *parent = 0);
    void guardar();
    
};

#endif // PATIOSFORM_H

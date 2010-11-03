#ifndef REMATESFORM_H
#define REMATESFORM_H

#include "ui_rematesform.h"
#include "modelhelper.hpp"

class RematesForm : public QGroupBox, public ModelHelper, private Ui::RematesForm {
    Q_OBJECT
public:
    RematesForm(const int &cuenta, QWidget *parent = 0);
    void guardar();
};

#endif // REMATESFORM_H

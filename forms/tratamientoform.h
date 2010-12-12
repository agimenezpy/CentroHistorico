#ifndef TRATAMIENTOFORM_H
#define TRATAMIENTOFORM_H

#include "ui_tratamientoform.h"
#include "modelhelper.hpp"

class QTableWidgetItem;

class TratamientoForm : public QGroupBox, public ModelHelper, private Ui::TratamientoForm {
    Q_OBJECT
public:
    TratamientoForm(const int &cuenta, QWidget *parent = 0);
    void guardar();

private:
    QTableWidgetItem *createTextItem();
    QTableWidgetItem *createCheckItem();
    void setTratamiento();
    bool save;
};

#endif // TRATAMIENTOFORM_H

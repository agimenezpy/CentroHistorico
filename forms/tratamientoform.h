#ifndef TRATAMIENTOFORM_H
#define TRATAMIENTOFORM_H

#include "ui_tratamientoform.h"

class QTableWidgetItem;

class TratamientoForm : public QGroupBox, private Ui::TratamientoForm {
    Q_OBJECT
public:
    TratamientoForm(const int &cuenta, QWidget *parent = 0);
    void guardar();

private:
    QTableWidgetItem *createTextItem();
    QTableWidgetItem *createCheckItem();
    void setTratamiento();
    bool save;
    int exist;
};

#endif // TRATAMIENTOFORM_H

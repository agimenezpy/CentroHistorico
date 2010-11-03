#ifndef FACHADAFORM_H
#define FACHADAFORM_H

#include "ui_fachadaform.h"
class QTableWidgetItem;

class FachadaForm : public QGroupBox, private Ui::FachadaForm {
    Q_OBJECT
public:
    FachadaForm(const int &cuenta, QWidget *parent = 0);
    void guardar();

private:
    void setFachada();
    QTableWidgetItem *createTableItem();
    bool save;
    int exist;
};

#endif // FACHADAFORM_H

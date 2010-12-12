#ifndef FACHADAFORM_H
#define FACHADAFORM_H

#include "ui_fachadaform.h"
#include "modelhelper.hpp"
#include <QStringList>

class QTableWidgetItem;

class FachadaForm : public QGroupBox, public ModelHelper, private Ui::FachadaForm {
    Q_OBJECT
public:
    FachadaForm(const int &cuenta, QWidget *parent = 0);
    void guardar();

private:
    void setFachada();
    QTableWidgetItem *createTableItem(bool check);
    void inicializarTabla(QTableWidget *tabla);
    void setTabla(QTableWidget *tabla);
    void setCoded(QTableWidget *tabla);
    int coded_values[5];
    bool save;
    QStringList otros;
};

#endif // FACHADAFORM_H

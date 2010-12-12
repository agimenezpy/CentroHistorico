#ifndef PATOLOGIAFORM_H
#define PATOLOGIAFORM_H

#include "ui_patologiaform.h"
#include "modelhelper.hpp"
#include <QStringList>

class PatologiaForm : public QGroupBox, public ModelHelper, private Ui::PatologiaForm {
    Q_OBJECT
public:
    PatologiaForm(const int &cuenta, QWidget *parent = 0);
    void guardar();
private:
    void inicializarTabla(QTableWidget *tabla, const int &offset);
    void setTabla(QTableWidget *tabla, const int &offset);
    void setCoded(QTableWidget *tabla, const int &offset);
    QTableWidgetItem *createTableItem(bool check);
    int coded_values[29];
    QStringList otros;
};

#endif // PATOLOGIAFORM_H

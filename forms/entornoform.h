#ifndef ENTORNOFORM_H
#define ENTORNOFORM_H

#include "ui_entornoform.h"
#include <QMap>
#include <QString>
#include <QVariant>

class QTableWidgetItem;

class EntornoForm : public QGroupBox, private Ui::EntornoForm {
    Q_OBJECT
public:
    EntornoForm(const int &cuenta, QWidget *parent = 0);
    ~EntornoForm();
    void guardar();

private:
    void setEntorno();
    QTableWidgetItem *createTableItem();
    int exist[5];
    QMap<QString, QVariant> *estados;
    QMap<QString, QVariant> *incidencias;
};

#endif // ENTORNOFORM_H

#ifndef ENTORNOFORM_H
#define ENTORNOFORM_H

#include "ui_entornoform.h"
#include "modelhelper.hpp"
#include <QMap>
#include <QString>
#include <QVariant>

class QTableWidgetItem;

class EntornoForm : public QGroupBox, public ModelHelper, private Ui::EntornoForm {
    Q_OBJECT
public:
    EntornoForm(const int &cuenta, QWidget *parent = 0);
    ~EntornoForm();
    void guardar();

private:
    void setEntorno();
    QTableWidgetItem *createTableItem();
    QMap<QString, QVariant> *estados;
    QMap<QString, QVariant> *incidencias;
};

#endif // ENTORNOFORM_H

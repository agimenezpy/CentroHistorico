#ifndef GENERALFORM_H
#define GENERALFORM_H

#include "ui_generalform.h"

class QSqlTableModel;
class QDataWidgetMapper;
class QModelIndex;

class GeneralForm : public QDialog, private Ui::GeneralForm {
    Q_OBJECT
public:
    GeneralForm(QWidget *parent = 0, QSqlTableModel *pModel = 0, QModelIndex *pIndex = 0);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void onBarrioTextChanged(QString barrio);
    void onEncuestadorTextChanged(QString encuestador);
    void updateCuentaCorriente();
    void guardar();
private:
    QSqlTableModel *model;
    QDataWidgetMapper *mapper;
    bool validar();
    bool check();
    bool isNew;
};

#endif // GENERALFORM_H

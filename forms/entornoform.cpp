#include "entornoform.h"
#include "util/combocolumnitemdelegate.h"
#include <QMap>
#include <QDataWidgetMapper>
#include <QSqlTableModel>
#include <QModelIndex>

EntornoForm::EntornoForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    QMap<QString, QVariant>* estados = new QMap<QString, QVariant>;
    estados->insert("Bueno", QChar('B'));
    estados->insert("Regular", QChar('R'));
    estados->insert("Malo", QChar('M'));
    entornoTable->setItemDelegateForColumn(1, new ComboColumnItemDelegate(estados, this));
    incidencias = new QMap<QString, QVariant>;
    incidencias->insert("Mas (+)", QChar('+'));
    incidencias->insert("Menos (-)", QChar('-'));
    entornoTable->setItemDelegateForColumn(2, new ComboColumnItemDelegate(incidencias,this));
    for (int row = 0; row < entornoTable->rowCount(); row++) {
        for (int col = 0; col < entornoTable->columnCount(); col++)
            entornoTable->setItem(row,col,createTableItem());
    }
    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
    construct(this,"entorno",cuentaEdit->text());
    mapper->addMapping(cuentaEdit, 0);
    init();
    setEntorno();
}

EntornoForm::~EntornoForm() {
    delete estados;
    delete incidencias;
}

QTableWidgetItem *EntornoForm::createTableItem() {
    QTableWidgetItem* item = new QTableWidgetItem;
    return item;
}

void EntornoForm::guardar() {
    QModelIndex indext,indexm;
    int offset = 1;
    for (int row = 0; row < entornoTable->rowCount() ; row++) {
        for (int col = 0; col < entornoTable->columnCount(); col++) {
            indext = entornoTable->model()->index(row,col);
            indexm = model->index(mapper->currentIndex(), col+offset);
            if (col == 0) {
                model->setData(indexm, entornoTable->model()->data(indext,Qt::DisplayRole));
            }
            else if (col == 1) {
                model->setData(indexm,entornoTable->model()->data(indext,Qt::UserRole));
            }
            else if (col == 2) {
                model->setData(indexm,entornoTable->model()->data(indext,Qt::UserRole));
            }
        }
        offset += 3;
    }
    this->submit();
}

void EntornoForm::setEntorno() {
    QModelIndex indext,indexm;
    int offset = 1;
    for (int row = 0; row < entornoTable->rowCount() ; row++) {
        for (int col = 0; col < entornoTable->columnCount(); col++) {
            indext = entornoTable->model()->index(row,col);
            indexm = model->index(mapper->currentIndex(), col+offset);
            if (col == 0) {
                entornoTable->model()->setData(indext,model->data(indexm),Qt::DisplayRole);
                entornoTable->item(row,col)->setText(model->data(indexm).toString());
            }
            else if (col == 1) {
                entornoTable->model()->setData(indext,model->data(indexm),Qt::UserRole);
                QString val = model->data(indexm).toString();
                if (val == QString("M"))
                    entornoTable->item(row,col)->setText("Malo");
                if (val == QString("B"))
                    entornoTable->item(row,col)->setText("Bueno");
                if (val == QString("R"))
                    entornoTable->item(row,col)->setText("Regular");
            }
            else if (col == 2) {
                entornoTable->model()->setData(indext,model->data(indexm),Qt::UserRole);
                QString val = model->data(indexm).toString();
                if (val == QString("+"))
                    entornoTable->item(row,col)->setText("Mas (+)");
                if (val == QString("-"))
                    entornoTable->item(row,col)->setText("Menos (-)");
            }
        }
        offset += 3;
    }
}

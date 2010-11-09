#include "entornoform.h"
#include "util/combocolumnitemdelegate.h"
#include <QMap>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QModelIndex>
#include <QMessageBox>

EntornoForm::EntornoForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
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
        exist[row] = 0;
    }
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
    QSqlQuery query;
    QModelIndex index;
    QSqlDatabase::database().transaction();
    int cuenta = cuentaEdit->text().toInt();
    bool error = false;

    QString updateStm = QString("UPDATE entorno SET %1 WHERE id = ?").arg(
    "cuenta_id = ?,categoria = ?,material = ?,estado = ?,incidencia = ?"
    );
    QString insertStm = QString("INSERT INTO entorno (%1) VALUES (?,?,?,?,?,?)").arg(
    "cuenta_id,categoria,material,estado,incidencia,id"
    );
    QStringList list;
    list << "VA" << "CA" << "VN" << "MO" << "OS";
    for (int row = 0; row < 4 && !error; row++) {
        if (exist[row] == 1)
            query.prepare(updateStm);
        else
            query.prepare(insertStm);
        query.bindValue(0,cuenta);
        query.bindValue(1,list.at(row));
        index = entornoTable->model()->index(row,0);
        query.bindValue(2,entornoTable->model()->data(index,Qt::DisplayRole));
        index = entornoTable->model()->index(row,1);
        query.bindValue(3,entornoTable->model()->data(index,Qt::UserRole));
        index = entornoTable->model()->index(row,2);
        query.bindValue(4,entornoTable->model()->data(index,Qt::UserRole));
        query.bindValue(5,cuenta*10+row);
        query.exec();
        if (query.lastError().isValid())
            error = true;
        if (!error)
            exist[row] = 1;
    }
    if (!error) {
        QSqlDatabase::database().commit();
        QMessageBox::information(this,"Datos guardados","Datos guardados con éxito");
    }
    else {
        QMessageBox::warning(this,"Error al guardar", query.lastError().text());
        QSqlDatabase::database().rollback();
    }
}

void EntornoForm::setEntorno() {
    QSqlQuery query;
    int cuenta = cuentaEdit->text().toInt();
    query.prepare("SELECT * FROM entorno WHERE cuenta_id = ? ORDER BY id");
    query.bindValue(0, cuenta);
    query.exec();
    int row = 0;
    cuenta = cuenta*10;
    QModelIndex index;
    while (query.next()) {
        row = query.value(0).toInt() - cuenta;
        for (int col = 0; col < entornoTable->columnCount(); col++) {
            index = entornoTable->model()->index(row,col);
            if (col == 0) {
                entornoTable->model()->setData(index,query.value(col+3),Qt::DisplayRole);
                entornoTable->item(row,col)->setText(query.value(col+3).toString());
            }
            else if (col == 1) {
                entornoTable->model()->setData(index,query.value(col+3),Qt::UserRole);
                QString val = query.value(col+3).toString();
                if (val == QString("M"))
                    entornoTable->item(row,col)->setText("Malo");
                if (val == QString("B"))
                    entornoTable->item(row,col)->setText("Bueno");
                if (val == QString("R"))
                    entornoTable->item(row,col)->setText("Regular");
            }
            else if (col == 2) {
                entornoTable->model()->setData(index,query.value(col+3),Qt::UserRole);
                QString val = query.value(col+3).toString();
                if (val == QString("+"))
                    entornoTable->item(row,col)->setText("Mas (+)");
                if (val == QString("-"))
                    entornoTable->item(row,col)->setText("Menos (-)");
            }
        }
        exist[row] = 1;
    }
}

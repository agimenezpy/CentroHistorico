#include "tratamientoform.h"
#include <QTableWidgetItem>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>

TratamientoForm::TratamientoForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);

    for (int row = 0; row < tratamientoTable->rowCount(); row++) {
        for (int col = 0 ; col < tratamientoTable->columnCount(); col++) {
            if (row == 3 || row == 5)
                tratamientoTable->setItem(row, col, createCheckItem());
            else
                tratamientoTable->setItem(row, col, createTextItem());
        }
    }

    QSqlQuery query;
    query.prepare("SELECT pisos FROM edificacion WHERE cuenta_id = ?");
    query.addBindValue(cuenta);
    int pisos = -1;
    save = false;
    query.exec();
    if (query.next()) {
        pisos = query.record().value(0).toInt();
        tratPisoEdit->setText(query.record().value(0).toString());
        save = true;
        setTratamiento();
    }
    else {
        QMessageBox::information(this,"Falta información","Aún no ha cargado datos del uso de suelo de la edificación");
    }

    for (int col = 0; col < tratamientoTable->columnCount(); col++) {
        if (col <= pisos)
            tratamientoTable->showColumn(col);
        else
            tratamientoTable->hideColumn(col);
    }
}

QTableWidgetItem *TratamientoForm::createTextItem() {
    QTableWidgetItem* item = new QTableWidgetItem;
    return item;
}

QTableWidgetItem *TratamientoForm::createCheckItem() {
    QTableWidgetItem* item = new QTableWidgetItem;
    item->setFlags(Qt::NoItemFlags);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    return item;
}

void TratamientoForm::setTratamiento() {
    QSqlQuery query;
    query.prepare("SELECT * FROM tratamiento_general WHERE cuenta_id = ? ORDER BY piso");
    query.bindValue(0, cuentaEdit->text());
    query.exec();
    int col = 0;
    exist = 0;
    while (query.next()) {
        for (int row = 0; row < tratamientoTable->rowCount(); row++) {
            if (row == 3 || row == 5) {
                if (query.value(row+2).toBool())
                    tratamientoTable->item(row,col)->setCheckState(Qt::Checked);
            }
            else
                tratamientoTable->item(row,col)->setText(query.value(row+2).toString());
        }
        col++;
    }
    exist = col;
}

void TratamientoForm::guardar() {
    if (!save)
        return;
    QString insertStm = "INSERT INTO tratamiento_general (cuenta_id,materiales,textura,color,alteraciones,letreros,otros,piso) VALUES (?,?,?,?,?,?,?,?)";
    QString updateStm = "UPDATE tratamiento_general SET cuenta_id = ?,materiales = ?,textura = ?,color = ?,alteraciones = ?,letreros = ?,otros = ? WHERE piso = ?";
    QSqlDatabase::database().transaction();
    QSqlQuery query;
    bool error = false;
    int cuenta = cuentaEdit->text().toInt();
    int pisos = tratPisoEdit->text().toInt();
    if (pisos < 4) {
        query.prepare("DELETE FROM tratamiento_general WHERE cuenta_id = ? AND piso > ?");
        query.addBindValue(cuenta);
        query.addBindValue(cuenta*10+pisos);
        query.exec();
        if (query.lastError().isValid())
            error = true;
    }

    if (pisos >= tratamientoTable->columnCount())
        pisos = tratamientoTable->columnCount() - 1;

    for (int col = 0; col <= pisos && !error; col++) {
        if (col < exist)
            query.prepare(updateStm);
        else
            query.prepare(insertStm);
        query.bindValue(0,cuenta);
        for (int row = 0; row < tratamientoTable->rowCount(); row++) {
             if (row == 3 || row == 5)
                 query.bindValue(row+1,tratamientoTable->item(row,col)->checkState() == Qt::Checked);
             else
                 query.bindValue(row+1,tratamientoTable->item(row,col)->text());
        }
        query.bindValue(7,cuenta*10+col);
        query.exec();
        if (query.lastError().isValid())
            error = true;
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

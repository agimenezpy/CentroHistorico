#include "fachadaform.h"
#include <QTableWidgetItem>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>

FachadaForm::FachadaForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);

    for (int row = 0; row < fachadaTable->rowCount(); row++)
        for (int col = 0 ; col < fachadaTable->columnCount(); col++)
            fachadaTable->setItem(row, col, createTableItem());

    QSqlQuery query;
    query.prepare("SELECT pisos FROM edificacion WHERE cuenta_id = ?");
    query.addBindValue(cuenta);
    int pisos = -1;
    save = false;
    query.exec();
    if (query.next()) {
        pisos = query.record().value(0).toInt();
        fachPisosEdit->setText(query.record().value(0).toString());
        save = true;
        setFachada();
    }
    else {
        QMessageBox::information(this,"Falta información","Aún no ha cargado datos del uso de suelo de la edificación");
    }

    for (int col = 0; col < fachadaTable->columnCount(); col++) {
        if (col <= pisos)
            fachadaTable->showColumn(col);
        else
            fachadaTable->hideColumn(col);
    }
}

QTableWidgetItem *FachadaForm::createTableItem() {
    QTableWidgetItem* item = new QTableWidgetItem;
    item->setFlags(Qt::NoItemFlags);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    return item;
}

void FachadaForm::setFachada() {
    QSqlQuery query;
    query.prepare("SELECT * FROM fachada WHERE cuenta_id = ? ORDER BY piso");
    query.bindValue(0, cuentaEdit->text());
    query.exec();
    int col = 0;
    exist = 0;
    while (query.next()) {
        for (int row = 0; row < fachadaTable->rowCount(); row++) {
            if (query.value(row+2).toBool())
                fachadaTable->item(row,col)->setCheckState(Qt::Checked);
        }
        col++;
    }
    exist = col;
}

void FachadaForm::guardar() {
    if (!save)
        return;
    QString insertStm = QString("INSERT INTO fachada (%1) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?)").arg(
    "cuenta_id,zocalo,columna_pilar,molduras,portada,galeria,arcos,adintelado,decorado,balcon_voladizo,balcon_recto,otros,piso"
    );
    QString updateStm = QString("UPDATE fachada SET %1 WHERE piso = ?").arg(
    "cuenta_id=?,zocalo=?,columna_pilar=?,molduras=?,portada=?,galeria=?,arcos=?,adintelado=?,decorado=?,balcon_voladizo=?,balcon_recto=?,otros=?"
    );
    QSqlDatabase::database().transaction();
    QSqlQuery query;
    bool error = false;
    int cuenta = cuentaEdit->text().toInt();
    int pisos = fachPisosEdit->text().toInt();
    if (pisos < 4) {
        query.prepare("DELETE FROM fachada WHERE cuenta_id = ? AND piso > ?");
        query.addBindValue(cuenta);
        query.addBindValue(cuenta*10+pisos);
        query.exec();
        if (query.lastError().isValid())
            error = true;
    }

    if (pisos >= fachadaTable->columnCount())
        pisos = fachadaTable->columnCount() - 1;

    for (int col = 0; col <= pisos && !error; col++) {
        if (col < exist)
            query.prepare(updateStm);
        else
            query.prepare(insertStm);
        query.bindValue(0,cuenta);
        for (int row = 0; row < fachadaTable->rowCount(); row++) {
             query.bindValue(row+1,fachadaTable->item(row,col)->checkState() == Qt::Checked);
        }
        query.bindValue(12,cuenta*10+col);
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


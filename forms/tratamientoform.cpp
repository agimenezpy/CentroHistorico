#include "tratamientoform.h"
#include <QTableWidgetItem>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

TratamientoForm::TratamientoForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
    construct(this,"tratamiento_general",cuentaEdit->text());
    mapper->addMapping(cuentaEdit, 0);
    init();

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
    QModelIndex indext,indexm;
    int offset = 1;
    int pisos = tratPisoEdit->text().toInt();
    for (int col = 0; col < tratamientoTable->columnCount() && col <= pisos; col++) {
        for (int row = 0; row < tratamientoTable->rowCount(); row++) {
            indext = tratamientoTable->model()->index(row,col);
            indexm = model->index(mapper->currentIndex(), row+offset);
            if (row == 3 || row == 5) {
                if (model->data(indexm).toBool())
                    tratamientoTable->item(row,col)->setCheckState(Qt::Checked);
            }
            else {
                tratamientoTable->model()->setData(indext,model->data(indexm),Qt::DisplayRole);
                tratamientoTable->item(row,col)->setText(model->data(indexm).toString());
            }
        }
        offset += 6;
    }
}

void TratamientoForm::guardar() {
    if (save) {
        QModelIndex indext,indexm;
        int offset = 1;
        int pisos = tratPisoEdit->text().toInt();
        for (int col = 0; col < tratamientoTable->columnCount() && col <= pisos; col++) {
            for (int row = 0; row < tratamientoTable->rowCount(); row++) {
                indext = tratamientoTable->model()->index(row,col);
                indexm = model->index(mapper->currentIndex(), row+offset);
                if (row == 3 || row == 5)
                    model->setData(indexm,tratamientoTable->item(row,col)->checkState() == Qt::Checked);
                else
                    model->setData(indexm, tratamientoTable->model()->data(indext,Qt::DisplayRole));
            }
            offset += 6;
        }
        this->submit();
    }
}

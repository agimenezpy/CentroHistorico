#include "fachadaform.h"
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QTableWidgetItem>
#include <QModelIndex>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

FachadaForm::FachadaForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
    construct(this,"fachada",cuentaEdit->text());
    mapper->addMapping(cuentaEdit, 0);
    init();

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
        inicializarTabla(fachadaTable);
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

void FachadaForm::inicializarTabla(QTableWidget *tabla) {
    for (int row = 0; row < tabla->rowCount()-1; row++) {
        for (int col = 0; col < tabla->columnCount(); col++)
            tabla->setItem(row,col,createTableItem(true));
    }
    for (int col = 0; col < tabla->columnCount(); col++)
        tabla->setItem(tabla->rowCount()-1,col,createTableItem(false));
    setTabla(tabla);
}

void FachadaForm::setTabla(QTableWidget *tabla) {
    if (!isNew) {
        QModelIndex index;
        for (int col = 0; col < tabla->columnCount(); col++) {
            index = model->index(mapper->currentIndex(), col+1);
            int coded_val = model->data(index).toInt();
            int row = tabla->rowCount() - 2;
            while (coded_val > 1) {
                if (coded_val % 2 == 1)
                    tabla->item(row,col)->setCheckState(Qt::Checked);
                coded_val /= 2;
                row -= 1;
            }
            if (coded_val == 1)
                tabla->item(row, col)->setCheckState(Qt::Checked);
            index = model->index(mapper->currentIndex(), col+6);
            tabla->item(tabla->rowCount() - 1, col)->setText(model->data(index).toString());
        }
    }
}

void FachadaForm::setCoded(QTableWidget *tabla) {
    int pisos = fachPisosEdit->text().toInt();
    for (int col = 0; col < tabla->columnCount(); col++) {
        int curInd = col;
        coded_values[curInd] = 0;
        int ini = 512;
        for (int row = 0; row < tabla->rowCount() - 1 && col <= pisos; row++) {
            if (tabla->item(row,col)->checkState() == Qt::Checked)
                coded_values[curInd] += ini;
            ini /= 2;
        }
        if (col <= pisos)
            otros.append(tabla->item(tabla->rowCount() - 1,col)->text());
        else
            otros.append("");
    }
}

QTableWidgetItem *FachadaForm::createTableItem(bool check) {
    QTableWidgetItem* item = new QTableWidgetItem;
    if (check) {
        item->setFlags(Qt::NoItemFlags);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
    }
    return item;
}

void FachadaForm::guardar() {
    if (save) {
        setCoded(fachadaTable);
        QModelIndex index;
        for (int i = 0; i < 5; i++) {
            index = model->index(mapper->currentIndex(), i+1);
            model->setData(index,coded_values[i]);
            index = model->index(mapper->currentIndex(), i+6);
            QString dato = otros.at(i);
            if (dato != "") {
                model->setData(index,dato);
            }
        }
        this->submit();
    }
}


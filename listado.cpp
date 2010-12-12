#include "listado.h"
#include "generalform.h"
#include "detallesform.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>

Listado::Listado(QWidget *parent) :
    QDialog(parent){
    setupUi(this);
    model = new QSqlTableModel(this);
    model->setTable("general");
    model->select();
    model->setHeaderData(2, Qt::Horizontal, "Número");
    model->setHeaderData(1, Qt::Horizontal, "Cuenta Corriente");
    model->setHeaderData(8, Qt::Horizontal, "Denominación");
    model->setHeaderData(3, Qt::Horizontal, "Dirección");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableView->setModel(model);
    for (int i = 0; i < 15; i++) {
        if ((i > 3 && i != 8) || i == 0)
            tableView->setColumnHidden(i, true);
    }
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->resizeColumnsToContents();
}

void Listado::addFicha() {
    GeneralForm *genForm = new GeneralForm(this, model);
    genForm->show();
}

void Listado::editFicha(QModelIndex index) {
    GeneralForm *genForm = new GeneralForm(this, model, &index);
    genForm->show();
}

void Listado::closeEvent(QCloseEvent *e)
{
    QDialog::closeEvent(e);
    this->parentWidget()->close();
}

QSqlTableModel *Listado::getModel() {
    return this->model;
}

void Listado::filtrar() {
    if (buscarEdit->text().size() > 0) {
        model->setFilter(QString("cuenta_corriente = %1").arg(buscarEdit->text()));
        model->select();
    }
    else if (model->filter().size() > 0) {
        model->setFilter("");
        model->select();
    }
}

void Listado::detalles() {
    QModelIndex index = tableView->currentIndex();
    if (index.isValid()) {
        int cuenta = model->record(index.row()).value("cuenta").toInt();
        DetallesForm *detallesForm = new DetallesForm(this,cuenta);
        detallesForm->show();
    }
}

void Listado::eliminar() {
    QModelIndex index = tableView->currentIndex();
    if (index.isValid()) {
        int cuenta = model->record(index.row()).value("cuenta").toInt();
        int respuesta = QMessageBox::question(this,"Eliminar Registro", "¿Está seguro que desea eliminar el registro seleccionado?", "Si", "No");
        if (respuesta == 0) {
            QSqlDatabase::database().transaction();
            QStringList tables;
            QSqlQuery query;
            tables << "acceso" << "entorno" << "remates"
                   << "estructura" << "servicio" << "conservacion"
                   << "fachada" << "cubierta"
                   << "dimension" << "imagen" << "tratamiento_general"
                   << "edad" << "ocupacion" << "uso_suelo"
                   << "edificacion" << "patio" << "valoracion"
                   << "patologia";
            bool error = false;
            for (int ta = 0; ta < tables.count() && !error; ta++) {
                query.prepare(QString("DELETE FROM %1 WHERE cuenta_id = ?").arg(tables.at(ta)));
                query.bindValue(0,cuenta);
                query.exec();
                if (query.lastError().isValid())
                    error = true;
            }
            if (!error) {
                model->removeRow(index.row());
                model->submitAll();
                tableView->reset();
                QSqlDatabase::database().commit();
                QMessageBox::information(this,"Eliminar registros","Datos eliminados con éxito");
            }
            else {
                QSqlDatabase::database().rollback();
                QMessageBox::warning(this,"Eliminar registros","No se pudeo eliminar el registro");
            }
        }
    }
}

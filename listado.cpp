#include "listado.h"
#include "generalform.h"
#include "detallesform.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>

Listado::Listado(QWidget *parent) :
    QDialog(parent){
    setupUi(this);
    model = new QSqlTableModel(this);
    model->setTable("general");
    model->select();
    model->setHeaderData(1, Qt::Horizontal, "Número");
    model->setHeaderData(0, Qt::Horizontal, "Cuenta Corriente");
    model->setHeaderData(7, Qt::Horizontal, "Denominación");
    model->setHeaderData(2, Qt::Horizontal, "Dirección");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableView->setModel(model);
    for (int i = 0; i < 14; i++) {
        if (i > 2 && i != 7)
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
        model->setFilter(QString("cuenta = %1").arg(buscarEdit->text()));
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

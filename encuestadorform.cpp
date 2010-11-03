#include "encuestadorform.h"
#include <QMessageBox>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlRelationalDelegate>

EncuestadorForm::EncuestadorForm(QWidget *parent) :
    QDialog(parent){
    setupUi(this);
    model = new QSqlRelationalTableModel(this);
    model->setTable("encuestador");
    model->setSort(Encuestador_Id, Qt::AscendingOrder);
    model->setHeaderData(Encuestador_Titulo, Qt::Horizontal, "Titulo");
    model->setHeaderData(Encuestador_Nombres, Qt::Horizontal, "Nombres");
    model->setHeaderData(Encuestador_Apellidos, Qt::Horizontal, "Apellidos");
    model->setRelation(1, QSqlRelation("titulo_encuestador","id","descripcion"));
    model->select();
    connect(model, SIGNAL(beforeInsert(QSqlRecord&)),
            this, SLOT(beforeInsertEncuestador(QSqlRecord&)));
    tableView->setModel(model);
    tableView->setColumnHidden(Encuestador_Id, true);
    tableView->setColumnWidth(Encuestador_Titulo, 50);
    tableView->setColumnWidth(Encuestador_Nombres, 100);
    tableView->setColumnWidth(Encuestador_Apellidos, 150);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setItemDelegateForColumn(1, new QSqlRelationalDelegate(this));
    if (model->rowCount() > 0)
        tableView->resizeColumnsToContents();
}

void EncuestadorForm::addEncuestador() {
    int row = model->rowCount();
    model->insertRow(row);
    QModelIndex index = model->index(row, Encuestador_Titulo);
    tableView->setCurrentIndex(index);
    tableView->edit(index);
}

void EncuestadorForm::beforeInsertEncuestador(QSqlRecord &record) {
    record.setValue("nombres", record.value("nombres").toString().toUpper());
    record.setValue("apellidos", record.value("apellidos").toString().toUpper());
    tableView->resizeColumnsToContents();
}

void EncuestadorForm::deleteEncuestador() {
    tableView->setFocus();
    QModelIndex index = tableView->currentIndex();
    if (!index.isValid())
      return;
    QSqlRecord record = model->record(index.row());
    QSqlTableModel cdModel;
    cdModel.setTable("general");
    cdModel.setFilter("encuestador_id = " + record.value("id").toString());
    cdModel.select();
    if (cdModel.rowCount() == 0) {
      model->removeRow(tableView->currentIndex().row());
    } else {
      QMessageBox::information(this,
              tr("Borrar Encuestaor"),
              tr("No se puede borrar %1 debido a que es referenciado "
                 "por una edificación.")
              .arg(record.value("nombres").toString()));
    }
}

void EncuestadorForm::closeEvent(QCloseEvent *e)
{
    QDialog::closeEvent(e);
    this->parentWidget()->close();
}

#include <QtGui/QMessageBox>
#include <QtSql>

#include "barrioform.h"
#include "util.h"

BarrioForm::BarrioForm(QWidget *parent) :
    QDialog(parent){
    setupUi(this);
    model = new QSqlTableModel(this);
    model->setTable("barrio");
    model->setSort(Barrio_Id, Qt::AscendingOrder);
    model->setHeaderData(Barrio_Nombre, Qt::Horizontal, "Nombre");
    model->select();
    connect(model, SIGNAL(beforeInsert(QSqlRecord &)),
            this, SLOT(beforeInsertBarrio(QSqlRecord &)));
    tableView->setModel(model);
    tableView->setColumnHidden(Barrio_Id, true);
    tableView->setColumnWidth(Barrio_Nombre, 40);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->resizeColumnsToContents();
}

void BarrioForm::addBarrio() {
    int row = model->rowCount();
    model->insertRow(row);
    QModelIndex index = model->index(row, Barrio_Nombre);
    tableView->setCurrentIndex(index);
    tableView->edit(index);
}

void BarrioForm::beforeInsertBarrio(QSqlRecord &record) {
    record.setValue("id", generateId("barrio"));
    record.setValue("nombre", record.value("nombre").toString().toUpper());
}

void BarrioForm::deleteBarrio() {
  tableView->setFocus();
  QModelIndex index = tableView->currentIndex();
  if (!index.isValid())
      return;
  QSqlRecord record = model->record(index.row());
  QSqlTableModel cdModel;
  cdModel.setTable("general");
  cdModel.setFilter("barrio_id = " + record.value("id").toString());
  cdModel.select();
  if (cdModel.rowCount() == 0) {
      model->removeRow(tableView->currentIndex().row());
  } else {
      QMessageBox::information(this,
              tr("Borrar Barrio"),
              tr("No se puede borrar %1 debido a que es referenciado "
                 "por una edificación.")
              .arg(record.value("nombre").toString()));
  }
}

void BarrioForm::closeEvent(QCloseEvent *e) {
    QDialog::closeEvent(e);
    this->parentWidget()->close();
}

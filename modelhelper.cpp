#include "modelhelper.hpp"
#include <QtGui/QMessageBox>
#include <QtSql>
#include <QDataWidgetMapper>

void ModelHelper::construct(QWidget *parent, QString tableName, QString column) {
    mapper = new QDataWidgetMapper(parent);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    model = new QSqlTableModel(parent);
    model->setTable(tableName);
    model->setFilter(QString("cuenta_id = %1").arg(column));
    model->select();
    mapper->setModel(model);
}

void ModelHelper::init() {
    mapper->submit();
    isNew = false;
    int row = model->rowCount();
    if (row == 0) {
        isNew = true;
        model->insertRow(row);
        mapper->setCurrentIndex(row);
    }
    else {
        mapper->toFirst();
    }
}

void ModelHelper::submit() {
    mapper->submit();
    //model->submitAll();
    if (model->lastError().isValid()) {
        QMessageBox::warning(0,QString("Error al guardar"), model->lastError().text());
        revert();
    }
    mapper->toFirst();
}

void ModelHelper::revert() {
    mapper->revert();
    //model->revertAll();
}

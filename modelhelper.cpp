#include "modelhelper.hpp"
#include <QtGui/QMessageBox>
#include <QtSql>
#include <QDataWidgetMapper>

void ModelHelper::construct(QWidget *parent, QString tableName, QString column) {
    mapper = new QDataWidgetMapper(parent);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    model = new QSqlTableModel(parent);
    model->setTable(tableName);
    model->setFilter(QString("cuenta = %1").arg(column));
    model->select();
    mapper->setModel(model);
}

void ModelHelper::init() {
    isNew = false;
    int row = model->rowCount();
    if (row > 0)
        isNew = true;
    mapper->submit();
    model->insertRow(row);
    mapper->setCurrentIndex(row);
}

void ModelHelper::submit() {
    mapper->submit();
    model->submitAll();
    if (model->lastError().isValid()) {
        QMessageBox::warning((QWidget*) this,QString("Error al guardar"), model->lastError().text());
        revert();
    }
}

void ModelHelper::revert() {
    mapper->revert();
    model->revertAll();
}

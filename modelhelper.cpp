#include "modelhelper.hpp"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QDataWidgetMapper>

void ModelHelper::construct(QWidget *parent, QString tableName, QString column) {
    self = parent;
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

bool ModelHelper::submit() {
    mapper->submit();
    if (model->lastError().isValid()) {
        QMessageBox::warning(self,"Error al guardar", model->lastError().text());
        revert();
        return false;
    }
    QMessageBox::information(self,"Datos guardados","Datos guardados con éxito");
    mapper->toFirst();
    return true;
}

void ModelHelper::revert() {
    mapper->revert();
}

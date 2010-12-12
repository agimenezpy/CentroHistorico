#include "encuestadorpickform.h"
#include <QMessageBox>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSqlRelation>
#include <QSqlRelationalDelegate>
#include <QDataWidgetMapper>
#include <QSqlError>

EncuestadorPickForm::EncuestadorPickForm(QWidget *parent) :
    QDialog(parent){
    setupUi(this);
    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    model = new QSqlRelationalTableModel(this);
    model->setTable("encuestador");
    model->setRelation(1, QSqlRelation("titulo_encuestador","id","descripcion"));
    model->select();

    QSqlTableModel *relModel = model->relationModel(1);
    tituloCmb->setModel(relModel);
    tituloCmb->setModelColumn(relModel->fieldIndex("descripcion"));

    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(tituloCmb, 1);
    mapper->addMapping(nombreEdit, 2);
    mapper->addMapping(apellidoEdit, 3);

    int row = model->rowCount();
    model->insertRow(row);
    mapper->setCurrentIndex(row);
    tituloCmb->setCurrentIndex(0);
}

void EncuestadorPickForm::submit() {
    nombreEdit->setText(nombreEdit->text().toUpper());
    apellidoEdit->setText(apellidoEdit->text().toUpper());
    mapper->submit();
    if (model->lastError().isValid()) {
        QMessageBox::warning(this,"Error al guardar", model->lastError().text());
        revert();
    }
    emit pick(0, nombreEdit->text(), apellidoEdit->text());
    mapper->toLast();
    this->close();
}

void EncuestadorPickForm::revert() {
    mapper->revert();
    this->close();
}

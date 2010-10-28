#include <QtGui/QMessageBox>
#include <QtGui/QCompleter>
#include <QValidator>
#include <QtSql>
#include <QDataWidgetMapper>
#include "generalform.h"
#include "util.h"

GeneralForm::GeneralForm(QWidget *parent, QSqlTableModel *pModel, QModelIndex *pIndex) :
    QDialog(parent) {
    setupUi(this);
    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    if (pModel != 0) {
        // Edit Desde el listado
        model = pModel;
    }
    else {
        model = new QSqlTableModel(this);
        model->setTable("general");
        model->setFilter("cuenta = -1");
        model->select();
        isNew = true;
    }
    mapper->setModel(model);
    mapper->addMapping(cuentaEdit, 0);
    mapper->addMapping(numeroEdit, 1);
    mapper->addMapping(direccionEdit, 2);
    mapper->addMapping(numeroEdifEdit, 3);
    mapper->addMapping(zonaEdit, 4);
    mapper->addMapping(manzanaEdit, 5);
    mapper->addMapping(loteEdit, 6);
    mapper->addMapping(denomEdit, 7);
    mapper->addMapping(denomHistEdit, 8);
    mapper->addMapping(barrioIdEdit, 9);
    mapper->addMapping(encIdEdit, 10);
    mapper->addMapping(fechaEdit, 11);
    mapper->addMapping(cataEdit, 12);
    mapper->addMapping(commentEdit, 13);

    mapper->submit();
    if (pIndex != 0) {
        isNew = false;
        mapper->setCurrentIndex(pIndex->row());
    }
    else {
        int row = model->rowCount();
        model->insertRow(row);
        isNew = true;
        mapper->setCurrentIndex(row);
    }

}

void GeneralForm::onBarrioTextChanged(QString barrio) {
    QSqlQuery query;
    query.prepare("SELECT id, nombre FROM barrio WHERE nombre = ?");
    query.addBindValue(barrio.toUpper());
    if (!query.exec()) {
        QMessageBox::warning(this, "Recuperar Barrios", query.lastError().text());
        return;
    }
    if (query.next()) {
        barrioIdEdit->setText(query.value(0).toString());
    }
    else if (barrio.size() > 1) {
        barrioIdEdit->setText("");
        query.prepare("SELECT id, nombre FROM barrio WHERE nombre LIKE ?");
        query.addBindValue(QString("%%1%").arg(barrio.toUpper()));
        if (!query.exec()) {
            QMessageBox::warning(this, "Recuperar Barrios", query.lastError().text());
            return;
        }
        QStringList wordList;
        while (query.next()) {
            wordList << query.value(1).toString();
        }
        if (wordList.size() > 0) {
            QCompleter *completer = new QCompleter(wordList, this);
            completer->setCaseSensitivity(Qt::CaseInsensitive);
            completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
            barrioEdit->setCompleter(completer);
        }
    }
}

void GeneralForm::onEncuestadorTextChanged(QString encuestador) {
    encIdEdit->setText("");
    QSqlQuery query;
    query.prepare("SELECT id, nombres || ' ' || apellidos FROM encuestador WHERE (nombres || ' ' || apellidos) = ?");
    query.addBindValue(encuestador.toUpper());
    if (!query.exec()) {
        QMessageBox::warning(this, "Recuperar Encuestador", query.lastError().text());
        return;
    }
    if (query.next()) {
        encIdEdit->setText(query.value(0).toString());
    }
    else if (encuestador.size() > 1) {
        query.prepare("SELECT id, nombres || ' ' || apellidos FROM encuestador WHERE (nombres || ' ' || apellidos) LIKE ?");
        query.addBindValue(QString("%%1%").arg(encuestador.toUpper()));
        if (!query.exec()) {
            QMessageBox::warning(this, "Recuperar Encuestador", query.lastError().text());
            return;
        }
        QStringList wordList;
        while (query.next()) {
            wordList << query.value(1).toString();
        }
        if (wordList.size() > 0) {
            QCompleter *completer = new QCompleter(wordList, this);
            completer->setCaseSensitivity(Qt::CaseInsensitive);
            completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
            encEdit->setCompleter(completer);
        }
    }
}

void GeneralForm::updateCuentaCorriente() {
    cuentaEdit->setText(QVariant(zonaEdit->text().toInt()*1000000 +
                                 manzanaEdit->text().toInt()*100 +
                                 loteEdit->text().toInt()).toString());
}

bool GeneralForm::validar() {
    QIntValidator *zonaVal = new QIntValidator(this);
    QIntValidator *intVal = new QIntValidator(this);
    zonaVal->setRange(10,15);
    QString s = numeroEdit->text();
    int pos = 0;
    if (s.length() == 0 || intVal->validate(s, pos) == QValidator::Invalid) {
        QMessageBox::information(this,
                                 "Al completar Número de Inventario",
                                 "<b>Número de Inventario</b> debe ser un número.");
        numeroEdit->setFocus();
        return false;
    }
    s = zonaEdit->text();
    if (s.length() == 0 || zonaVal->validate(s, pos) != QValidator::Acceptable) {
        QMessageBox::information(this,
                                 "Al completar Zona",
                                 "<b>Zona</b> inválida.");
        zonaEdit->setFocus();
        return false;
    }
    s = manzanaEdit->text();
    if (s.length() == 0 || intVal->validate(s, pos) == QValidator::Invalid) {
        QMessageBox::information(this,
                                 "Al completar Manzana",
                                 "<b>Manzana</b> debe ser un número.");
        manzanaEdit->setFocus();
        return false;
    }
    s = loteEdit->text();
    if (s.length() == 0 || intVal->validate(s, pos) == QValidator::Invalid) {
        QMessageBox::information(this,
                                 "Al completar Lote",
                                 "<b>Lote</b> debe ser un número.");
        loteEdit->setFocus();
        return false;
    }
    s = barrioIdEdit->text();
    if (s.length() == 0 || intVal->validate(s, pos) == QValidator::Invalid) {
        QMessageBox::information(this,
                                 "Al completar Barrio",
                                 "<b>Barrio</b> debe ser un número.");
        barrioEdit->setFocus();
        return false;
    }
    s = encIdEdit->text();
    if (s.length() == 0 || intVal->validate(s, pos) == QValidator::Invalid) {
        QMessageBox::information(this,
                                 "Al completar Encuestador",
                                 "<b>Encuestador</b> debe ser un número.");
        encEdit->setFocus();
        return false;
    }
    if (cataEdit->text().length() == 0) {
        QMessageBox::information(this,
                                 "Al completar Catalogación",
                                 "<b>Catalogación</b> no debe ser vacio.");
        cataEdit->setFocus();
        return false;
    }

    return true;
}

bool GeneralForm::check() {
    QString title("Al completar %1");
    QString msg("<b>%1</b> ya existe.");
    if (exist("general","cuenta",cuentaEdit->text())) {
        QMessageBox::information(this,
                                 title.arg("Cuenta Corriente"),
                                 msg.arg("Cuenta Corriente"));
        cuentaEdit->setFocus();
        return false;
    }
    if (exist("general","numero_inventario",numeroEdit->text())) {
        QString item("Número de Inventario");
        QMessageBox::information(this,
                                 title.arg(item),
                                 msg.arg(item));
        numeroEdit->setFocus();
        return false;
    }
    return true;
}

void GeneralForm::guardar() {
    if (validar() && (!isNew || check())) {
        mapper->submit();
        model->submitAll();
        if (model->lastError().isValid()) {
            QMessageBox::warning(this,"Error al guardar", model->lastError().text());
            mapper->revert();
            model->revertAll();
        }
        else
            isNew = false;
        close();
    }
}

void GeneralForm::closeEvent(QCloseEvent *event) {
    QDialog::closeEvent(event);
    if (isNew)
        model->removeRow(model->rowCount()-1);
    model->submitAll();
}

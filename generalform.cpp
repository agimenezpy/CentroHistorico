#include "generalform.h"
#include <QMessageBox>
#include <QCompleter>
#include <QValidator>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDataWidgetMapper>
#include "util.h"
#include "forms/encuestadorpickform.h"

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
    mapper->addMapping(cuentaCorrienteEdit, 1);
    mapper->addMapping(numeroEdit, 2);
    mapper->addMapping(direccionEdit, 3);
    mapper->addMapping(numeroEdifEdit, 4);
    mapper->addMapping(zonaEdit, 5);
    mapper->addMapping(manzanaEdit, 6);
    mapper->addMapping(loteEdit, 7);
    mapper->addMapping(denomEdit, 8);
    mapper->addMapping(denomHistEdit, 9);
    mapper->addMapping(barrioIdEdit, 10);
    mapper->addMapping(encIdEdit, 11);
    mapper->addMapping(fechaEdit, 12);
    mapper->addMapping(cataEdit, 13);
    mapper->addMapping(commentEdit, 14);

    mapper->submit();
    if (pIndex != 0) {
        isNew = false;
        mapper->setCurrentIndex(pIndex->row());
        barrioEdit->setText(lookup("barrio","nombre",barrioIdEdit->text().toInt()));
        encEdit->setText(lookup("encuestador","nombres || ' ' || apellidos",encIdEdit->text().toInt()));
    }
    else {
        int row = model->rowCount();
        model->insertRow(row);
        isNew = true;
        mapper->setCurrentIndex(row);
    }
    QIntValidator *val = new QIntValidator(this);
    val->setBottom(0);
    zonaEdit->setValidator(val);
    manzanaEdit->setValidator(val);
    loteEdit->setValidator(val);

    QRegExp rxTmp("\\d+(,\\d+)*");
    QRegExpValidator *rx = new QRegExpValidator(rxTmp, this);
    numeroEdifEdit->setValidator(rx);

    connect(model, SIGNAL(beforeInsert(QSqlRecord&)),
            this, SLOT(beforeInsertGeneral(QSqlRecord&)));
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
    cuentaCorrienteEdit->setText(QVariant(getCuentaCorriente()).toString());
}

bool GeneralForm::validar() {
    QIntValidator *zonaVal = new QIntValidator(this);
    QIntValidator *intVal = new QIntValidator(this);
    QRegExp rx("\\d{2}-\\d{4}-\\d{2}");
    QRegExpValidator *cuentaVal = new QRegExpValidator(rx,this);
    zonaVal->setRange(10,15);
    int pos = 0;
    QString s = cuentaCorrienteEdit->text();
    if (s.length() == 0 || cuentaVal->validate(s, pos) != QValidator::Acceptable) {
        QMessageBox::information(this,
                                 "Al completar la Cuenta",
                                 "<b>Cuenta</b> inválida.");
        cuentaCorrienteEdit->setFocus();
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

void GeneralForm::guardar() {
    if (validar() && !isNew) {
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

QString GeneralForm::lookup(QString table, QString column, int id) {
    QSqlQuery query;
    query.prepare(QString("SELECT %1 FROM %2 WHERE id = ?").arg(column,table));
    query.bindValue(0,QVariant(id));
    query.exec();
    QString result = "";
    if (query.next())
        result = query.value(0).toString();
    return result;
}

int GeneralForm::getId() {
    QSqlQuery query;
    query.prepare("SELECT MAX(id) FROM general WHERE cuenta_corriente = ?");
    query.bindValue(0, cuentaCorrienteEdit->text());
    query.exec();
    int id = 0;
    if (query.next())
        id = query.value(0).toInt() + 1;
    return id;
}

int GeneralForm::getCuentaCorriente() {
    return zonaEdit->text().toInt()*1000000 +
            manzanaEdit->text().toInt()*100 +
            loteEdit->text().toInt();
}

void GeneralForm::beforeInsertGeneral(QSqlRecord &record) {
    int base = getCuentaCorriente()*100;
    int last = getId();
    if (last == 0)
        last = base;
    else
        last = last - base + 1;
    record.setValue("cuenta",last);
}

void GeneralForm::onCuentaCorrienteTextChanged(QString cuenta) {
    QStringList lista = cuenta.split("-");
    for (int i = 0; i < lista.size(); i++) {
        if (i == 0 && lista.at(i).size() > 0)
            zonaEdit->setText(lista.at(i));
        if (i == 1 && lista.at(i).size() > 0)
            manzanaEdit->setText(lista.at(i));
        if (i == 2 && lista.at(i).size() > 0)
            loteEdit->setText(lista.at(i));
    }
}

void GeneralForm::abrirNuevoEncuestador() {
    encuesta = new EncuestadorPickForm;
    encuesta->setAttribute(Qt::WA_DeleteOnClose);
    encuesta->show();
    encuesta->setFocus(Qt::ActiveWindowFocusReason);
    connect(encuesta, SIGNAL(destroyed()), this, SLOT(hideEncuesta()));
    connect(encuesta, SIGNAL(pick(int,QString,QString)), this, SLOT(onPickEncuesta(int,QString,QString)));
}

void GeneralForm::onPickEncuesta(int id, QString nombres, QString apellidos) {
    encEdit->setText(nombres + " " + apellidos);
}

void GeneralForm::hideEncuesta() {
    disconnect(encuesta, SIGNAL(destroyed()), this, SLOT(hideEncuesta()));
    encuesta = 0;
}

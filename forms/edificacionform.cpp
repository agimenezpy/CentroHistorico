#include "edificacionform.h"
#include "util/combodelegate.h"
#include <QDataWidgetMapper>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

EdificacionForm::EdificacionForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    edifEdificacionCmb->setItemData(0,QChar('\0'));
    edifEdificacionCmb->addItem("Integrada", QChar('I'));
    edifEdificacionCmb->addItem("No integrada", QChar('N'));
    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
    construct(this,"edificacion", cuentaEdit->text());
    mapper->setItemDelegate(new ComboDelegate(this));
    mapper->addMapping(cuentaEdit, 0);
    mapper->addMapping(edifSuperficieEdit, 1);
    mapper->addMapping(edifTotSuperficieEdit, 2);
    mapper->addMapping(edifPisosEdit, 3);
    mapper->addMapping(edifEdificacionCmb, 4);
    init();
    QIntValidator *val = new QIntValidator(this);
    val->setBottom(1);
    edifPisosEdit->setValidator(val);
    QDoubleValidator* val2 = new QDoubleValidator(this);
    val2->setBottom(0);
    edifSuperficieEdit->setValidator(val2);
    edifTotSuperficieEdit->setValidator(val2);
    for (int row = 0; row < edifUsoSueloTable->rowCount(); row++)
        for (int col = 0; col < edifUsoSueloTable->columnCount(); col++)
            edifUsoSueloTable->setItem(row,col,createTableItem());
    for (int col = 0; col < edifUsoSueloTable->columnCount(); col++)
        edifUsoSueloTable->setColumnWidth(col,25);
    modificarEdificacion("0");
    setUsoSuelo();
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void EdificacionForm::modificarEdificacion(QString textChanged) {
    int pos = 0;
    if (textChanged.size() > 0) {
        pos = textChanged.toInt();
    }
    for (int j = 0; j < edifUsoSueloTable->columnCount(); j++) {
        if (j <= pos)
            edifUsoSueloTable->showColumn(j);
        else
            edifUsoSueloTable->hideColumn(j);
    }
}

QTableWidgetItem *EdificacionForm::createTableItem() {
    QTableWidgetItem* item = new QTableWidgetItem;
    item->setFlags(Qt::NoItemFlags);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    return item;
}

void EdificacionForm::guardar() {
    if (this->submit()) {
        QSqlQuery query;
        QSqlDatabase::database().transaction();
        int cuenta = cuentaEdit->text().toInt();
        int pisos = edifPisosEdit->text().toInt();
        bool error = false;
        if (pisos < 4) {
            query.prepare("DELETE FROM uso_suelo WHERE cuenta_id = ? AND piso > ?");
            query.addBindValue(cuenta);
            query.addBindValue(cuenta*10+pisos);
            query.exec();
            if (query.lastError().isValid())
                error = true;
        }

        //query.prepare("INSERT INTO uso_suelo VALUES (?,?,?,?,?,?,?,?,?,?,?,?)");
        QString updateStm = QString("UPDATE uso_suelo SET %1 WHERE piso = ?").arg(
        "cuenta_id = ?,adm_oficina = ?,comercio_gm = ?,comercio_pm = ?,despensa = ?,bar_cafe = ?,hotel = ?,sanidad = ?,recreo = ?,religioso = ?,otros = ?"
        );
        QString insertStm = QString("INSERT INTO uso_suelo (%1) VALUES (?,?,?,?,?,?,?,?,?,?,?,?)").arg(
        "cuenta_id,adm_oficina,comercio_gm,comercio_pm,despensa,bar_cafe,hotel,sanidad,recreo,religioso,otros,piso"
        );
        if (pisos >= edifUsoSueloTable->columnCount())
            pisos = edifUsoSueloTable->columnCount() - 1;

        for (int col = 0; col <= pisos && !error ; col++) {
            if (col < exist)
                query.prepare(updateStm);
            else
                query.prepare(insertStm);
            query.bindValue(0,cuenta);
            for (int row = 0; row < edifUsoSueloTable->rowCount(); row++)
                query.bindValue(row+1,edifUsoSueloTable->item(row,col)->checkState() == Qt::Checked);
            query.bindValue(11,cuenta*10 + col);
            query.exec();
        }
        if (!error) {
            QSqlDatabase::database().commit();
        }
        else {
            QMessageBox::warning(this,"Error al guardar", query.lastError().text());
            QSqlDatabase::database().rollback();
        }
    }
}

void EdificacionForm::setUsoSuelo() {
    if (!isNew) {
        modificarEdificacion(edifPisosEdit->text());
        QSqlQuery query;
        query.prepare("SELECT * FROM uso_suelo WHERE cuenta_id = ? ORDER BY piso");
        query.bindValue(0, cuentaEdit->text().toInt());
        query.exec();
        int col = 0;
        while (query.next()) {
            for (int row = 0; row < edifUsoSueloTable->rowCount(); row++) {
                    if (query.value(row+2).toBool())
                        edifUsoSueloTable->item(row,col)->setCheckState(Qt::Checked);
            }
            col++;
        }
        exist = col;
    }
    else
        exist = 0;
}

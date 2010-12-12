#include "edificacionform.h"
#include "util/combodelegate.h"
#include <QDataWidgetMapper>
#include <QSqlTableModel>
#include <QModelIndex>

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
    setTabla(edifUsoSueloTable);
}

void EdificacionForm::setTabla(QTableWidget *tabla) {
    int offset = 5;
    if (!isNew) {
        QModelIndex index;
        for (int col = 0; col < tabla->columnCount(); col++) {
            index = model->index(mapper->currentIndex(), col+offset);
            int coded_val = model->data(index).toInt();
            int row = tabla->rowCount() - 1;
            while (coded_val > 1) {
                if (coded_val % 2 == 1)
                    tabla->item(row,col)->setCheckState(Qt::Checked);
                coded_val /= 2;
                row -= 1;
            }
            if (coded_val == 1)
                tabla->item(row, col)->setCheckState(Qt::Checked);
        }
        modificarEdificacion(edifPisosEdit->text());
    }
}

void EdificacionForm::setCoded(QTableWidget *tabla) {
    int pisos = edifPisosEdit->text().toInt();
    for (int col = 0; col < tabla->columnCount(); col++) {
        int curInd = col;
        coded_values[curInd] = 0;
        int ini = 512;
        for (int row = 0; row < tabla->rowCount() && col <= pisos; row++) {
            if (tabla->item(row,col)->checkState() == Qt::Checked)
                coded_values[curInd] += ini;
            ini /= 2;
        }
    }
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
    setCoded(edifUsoSueloTable);
    QModelIndex index;
    for (int i = 0; i < 5; i++) {
        index = model->index(mapper->currentIndex(), i+5);
        model->setData(index,coded_values[i]);
    }
    this->submit();
}

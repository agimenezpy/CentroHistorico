#include "patologiaform.h"
#include <QSqlTableModel>
#include <QDataWidgetMapper>

PatologiaForm::PatologiaForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    cuentaEdit->setText(QString("%1").arg(cuenta));
    cuentaEdit->setVisible(false);
    construct(this,"patologia",cuentaEdit->text());
    mapper->addMapping(cuentaEdit, 0);
    init();
    inicializarTabla(tratamientoTable,1);
    inicializarTabla(fachadaTable,6);
    inicializarTabla(huecosTable,11);
    inicializarTabla(rematesTable,16);
    inicializarTabla(cubiertaTable,20);
    inicializarTabla(estructuraTable,24);
}

void PatologiaForm::inicializarTabla(QTableWidget *tabla, const int &offset) {
    for (int row = 0; row < tabla->rowCount(); row++)
        for (int col = 0; col < tabla->columnCount(); col++)
            tabla->setItem(row,col,createTableItem());
    setTabla(tabla,offset);
}

void PatologiaForm::setTabla(QTableWidget *tabla, const int &offset) {
    if (!isNew) {
        QModelIndex index;
        for (int row = 0; row < tabla->rowCount(); row++) {
            index = model->index(mapper->currentIndex(), row+offset);
            int coded_val = model->data(index).toInt();
            int col = tabla->columnCount() - 1;
            while (coded_val > 1) {
                if (coded_val % 2 == 1)
                    tabla->item(row,col)->setCheckState(Qt::Checked);
                coded_val /= 2;
                col -= 1;
            }
            if (coded_val == 1)
                tabla->item(row, col)->setCheckState(Qt::Checked);
        }
    }
}

void PatologiaForm::setCoded(QTableWidget *tabla, const int &offset) {
    for (int row = 0; row < tabla->rowCount(); row++) {
        int curInd = row+offset;
        coded_values[curInd] = 0;
        int ini = 1024;
        for (int col = 0; col < tabla->columnCount(); col++) {
            if (tabla->item(row,col)->checkState() == Qt::Checked)
                coded_values[curInd] += ini;
            ini /= 2;
        }
    }
}

QTableWidgetItem *PatologiaForm::createTableItem() {
    QTableWidgetItem* item = new QTableWidgetItem;
    item->setFlags(Qt::NoItemFlags);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    return item;
}

void PatologiaForm::guardar() {
    setCoded(tratamientoTable,0);
    setCoded(fachadaTable,5);
    setCoded(huecosTable,10);
    setCoded(rematesTable,15);
    setCoded(cubiertaTable,19);
    setCoded(estructuraTable,23);
    QModelIndex index;
    for (int i = 0; i < 29; i++) {
        index = model->index(mapper->currentIndex(), i+1);
        model->setData(index,coded_values[i]);
    }
    this->submit();
}

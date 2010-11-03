#include "fotosform.h"
#include <QFileDialog>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRelation>
#include <QSqlRecord>
#include <QImage>

FotosForm::FotosForm(const int &cuenta, QWidget *parent) : QGroupBox(parent) {
    setupUi(this);
    model = new QSqlRelationalTableModel(this);
    model->setTable("imagen");
    model->setSort(0, Qt::AscendingOrder);
    model->setFilter(QString("cuenta_id = %1").arg(cuenta));
    model->setHeaderData(2, Qt::Horizontal, "Titulo");
    model->setHeaderData(3, Qt::Horizontal, "Categoria");
    model->setRelation(3, QSqlRelation("tipo_imagen","id","descripcion"));
    model->select();
    tableView->setModel(model);
    tableView->setColumnHidden(0,true);
    tableView->setColumnHidden(1,true);
    tableView->setColumnHidden(4,true);
    tableView->setColumnWidth(2, 200);
    tableView->setColumnWidth(3, 80);
    tableView->setItemDelegateForColumn(3, new QSqlRelationalDelegate(this));
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ccc = cuenta;
}

void FotosForm::mostrarImagen(QModelIndex index) {
    QImage imagen(model->record(index.row()).value(4).toString());
    if (!imagen.isNull()) {
        imageLabel->setPixmap(
                QPixmap::fromImage(
                        imagen.width() > imagen.height() ?
                            imagen.scaledToWidth(320) :
                            imagen.scaledToHeight(240))
                );
    }
    else {
        imageLabel->setPixmap(0);
        imageLabel->setText("Imagen no disponible");
    }
}

void FotosForm::agregarImagen() {
    int row = model->rowCount();
    model->insertRow(row);
    QModelIndex index = model->index(row, 1);
    model->setData(index,QVariant(ccc));
    index = model->index(row, 2);
    tableView->setCurrentIndex(index);
    tableView->edit(index);
}

void FotosForm::eliminarImagen() {
    tableView->setFocus();
    QModelIndex index = tableView->currentIndex();
    if (index.isValid()) {
        model->removeRow(index.row());
    }
}

void FotosForm::asignarFoto() {
    QModelIndex index = tableView->currentIndex();
    if (index.isValid()) {
        QString filename = QFileDialog::getOpenFileName(this,
                                                        "Elija una imagen",
                                                        QDir::currentPath(),
                                                        "Imagenes (*.png *.jpg *.bmp *.jpeg *.gif *.tif)");
        model->setData(model->index(index.row(), 4), filename);
        model->submit();
        mostrarImagen(index);
    }
}

#ifndef FOTOSFORM_H
#define FOTOSFORM_H

#include "ui_fotosform.h"
#include <QModelIndex>

class QSqlRelationalTableModel;

class FotosForm : public QGroupBox, private Ui::FotosForm {
    Q_OBJECT
public:
    FotosForm(const int &cuenta, QWidget *parent = 0);

private slots:
    void mostrarImagen(QModelIndex index);
    void agregarImagen();
    void eliminarImagen();
    void asignarFoto();

private:
    QSqlRelationalTableModel *model;
    int ccc;
};

#endif // FOTOSFORM_H

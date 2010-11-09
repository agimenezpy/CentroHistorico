#ifndef LISTADO_H
#define LISTADO_H

#include "ui_listado.h"

class QSqlTableModel;
class QModelIndex;

class Listado : public QDialog, private Ui::Listado {
    Q_OBJECT
public:
    Listado(QWidget *parent = 0);
    QSqlTableModel *getModel();

signals:
    void showNuevo();

private slots:
    void addFicha();
    void editFicha(QModelIndex index);
    void filtrar();
    void detalles();
    void eliminar();

protected:
    void closeEvent(QCloseEvent *e);

private:
    QSqlTableModel *model;
};

#endif // LISTADO_H

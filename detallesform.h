#ifndef DETALLESFORM_H
#define DETALLESFORM_H

#include "ui_detallesform.h"
class QTreeWidgetItem;

class DetallesForm : public QDialog, private Ui::DetallesForm {
    Q_OBJECT
public:
    DetallesForm(QWidget *parent = 0, int cuenta = 0);

private slots:
    void cambiarFormulario(QTreeWidgetItem *item, int column);
    void guardarActual();
signals:
    void guardar();

protected:
    void closeEvent(QCloseEvent *event);
private:
    QWidget* actualForm;
    int cuenta;
    QString last;
};

#endif // DETALLESFORM_H

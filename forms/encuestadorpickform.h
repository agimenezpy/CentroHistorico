#ifndef ENCUESTADORPICKFORM_H
#define ENCUESTADORPICKFORM_H

#include "ui_encuestadorpickform.h"

class QDataWidgetMapper;
class QSqlRelationalTableModel;

class EncuestadorPickForm : public QDialog, public Ui::EncuestadorPickForm {
    Q_OBJECT
public:
    EncuestadorPickForm(QWidget *parent = 0);

signals:
    void pick(int id, QString nombre, QString apellido);

private slots:
    void submit();
    void revert();

private:
    QDataWidgetMapper *mapper;
    QSqlRelationalTableModel *model;
};

#endif // ENCUESTADORPICKFORM_H

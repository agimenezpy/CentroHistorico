#ifndef ENCUESTADORFORM_H
#define ENCUESTADORFORM_H

#include "ui_encuestadorform.h"

class QSqlRecord;
class QSqlRelationalTableModel;

class EncuestadorForm : public QDialog, private Ui::EncuestadorForm {
    Q_OBJECT
public:
    EncuestadorForm(QWidget *parent = 0);

private slots:
    void addEncuestador();
    void deleteEncuestador();
    void beforeInsertEncuestador(QSqlRecord &record);

protected:
    void closeEvent(QCloseEvent *e);

private:
    enum {
        Encuestador_Id = 0,
        Encuestador_Titulo,
        Encuestador_Nombres,
        Encuestador_Apellidos
    };
    QSqlRelationalTableModel *model;
};

#endif // ENCUESTADORFORM_H

#ifndef ENCUESTADORFORM_H
#define ENCUESTADORFORM_H

#include "ui_encuestadorform.h"

class QSqlRecord;
class QSqlTableModel;

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
        Encuestador_Nombres = 1,
        Encuestador_Apellidos = 2
    };
    QSqlTableModel *model;
};

#endif // ENCUESTADORFORM_H

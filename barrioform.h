#ifndef BARRIOFORM_H
#define BARRIOFORM_H

#include "ui_barrioform.h"

class QSqlTableModel;
class QSqlRecord;

class BarrioForm : public QDialog, private Ui::BarrioForm {
    Q_OBJECT
public:
    BarrioForm(QWidget *parent = 0);

private slots:
    void addBarrio();
    void deleteBarrio();
    void beforeInsertBarrio(QSqlRecord &record);

protected:
    void closeEvent(QCloseEvent *e);

private:
    enum {
        Barrio_Id = 0,
        Barrio_Nombre = 1
    };
    QSqlTableModel *model;
};

#endif // BARRIOFORM_H


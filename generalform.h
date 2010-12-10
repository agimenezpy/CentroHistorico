#ifndef GENERALFORM_H
#define GENERALFORM_H

#include "ui_generalform.h"

class QSqlTableModel;
class QSqlRecord;
class QDataWidgetMapper;
class QModelIndex;
class EncuestadorPickForm;

class GeneralForm : public QDialog, private Ui::GeneralForm {
    Q_OBJECT
public:
    GeneralForm(QWidget *parent = 0, QSqlTableModel *pModel = 0, QModelIndex *pIndex = 0);

protected:
    void closeEvent(QCloseEvent *event);

private slots:   
    void onBarrioTextChanged(QString barrio);
    void onEncuestadorTextChanged(QString encuestador);
    void updateCuentaCorriente();
    void guardar();
    void beforeInsertGeneral(QSqlRecord &record);
    void onCuentaCorrienteTextChanged(QString cuenta);
    void abrirNuevoEncuestador();
    void hideEncuesta();
    void onPickEncuesta(int id, QString nombres, QString apellidos);
private:
    QSqlTableModel *model;
    QDataWidgetMapper *mapper;
    EncuestadorPickForm *encuesta;
    bool validar();
    bool check();
    bool isNew;
    QString lookup(QString table, QString column, int id);
    int getId();
    int getCuentaCorriente();
};

#endif // GENERALFORM_H

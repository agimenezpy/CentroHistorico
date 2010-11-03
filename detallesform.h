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
    void siguiente();
    void anterior();

signals:
    void guardar();

private:
    QWidget* actualForm;
    int cuenta;
    enum {
        DIMENSION = 0,
        EDIFICACION = 10,
        PATIOS = 11,
        ACCESO = 12,
        ENTORNO = 13,
        SERVICIOS = 2,
        OCUPACION = 3,
        EDAD = 4,
        TRATAMIENTO = 50,
        FACHADA = 51,
        REMATES = 52,
        CUBIERTA = 53,
        ESTRUCTURA = 54,
        PATOLOGIAS = 6,
        CONSERVACION = 7,
        VALORACION = 8,
        FOTOS = 9
    };
};

#endif // DETALLESFORM_H

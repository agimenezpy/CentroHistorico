#include "entornoform.h"
#include "util/combocolumnitemdelegate.h"
#include <QMap>

EntornoForm::EntornoForm(const int &cuenta, QWidget *parent) :
    QGroupBox(parent){
    setupUi(this);
    QMap<QString, QVariant>* pares = new QMap<QString, QVariant>;
    pares->insert("Bueno", QChar('B'));
    pares->insert("Regular", QChar('R'));
    pares->insert("Malo", QChar('M'));
    entornoTable->setItemDelegateForColumn(1, new ComboColumnItemDelegate(pares, this));
    pares = new QMap<QString, QVariant>;
    pares->insert("Mas (+)", QChar('+'));
    pares->insert("Menos (-)", QChar('-'));
    entornoTable->setItemDelegateForColumn(2, new ComboColumnItemDelegate(pares,this));
}

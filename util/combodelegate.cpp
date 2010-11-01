#include "combodelegate.h"
#include <QComboBox>

ComboDelegate::ComboDelegate(QObject *parent) : QItemDelegate(parent) {}

void ComboDelegate::setEditorData(QWidget *editor,
                       const QModelIndex &index) const
{
    QComboBox *cmb = qobject_cast<QComboBox*>(editor);
    if (!cmb) {
        QItemDelegate::setEditorData(editor, index);
        return;
    }
    int i = 0;
    cmb->setCurrentIndex(0);
    for (i = 1; i < cmb->count(); i++) {
        if (index.data() == cmb->itemData(i, Qt::UserRole))
            break;
    }
    if (i < cmb->count())
        cmb->setCurrentIndex(i);
}

void ComboDelegate::setModelData(QWidget *editor,
                     QAbstractItemModel *model,
                     const QModelIndex &index) const
{
    QComboBox *cmb = qobject_cast<QComboBox*>(editor);
    if (!cmb) {
        QItemDelegate::setModelData(editor, model, index);
        return;
    }

    QVariant value = cmb->itemData(cmb->currentIndex(), Qt::UserRole);
    if (value.isValid())
        model->setData(index, value);
}

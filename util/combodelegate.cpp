#include "combodelegate.h"
#include <QtGui/QComboBox>
#include <QMetaProperty>

ComboDelegate::ComboDelegate(QObject *parent) : QItemDelegate(parent) {}

void ComboDelegate::setEditorData(QWidget *editor,
                       const QModelIndex &index) const
{
    if (!editor->metaObject()->userProperty().isValid()) {
        if (editor->property("currentIndex").isValid()) {
            QComboBox *cmb = static_cast<QComboBox*>(editor);
            int idx = 0;
            for (int i = 1; i < cmb->count() && idx != 0; i++) {
                if (index.data() == cmb->itemData(i, Qt::UserRole))
                    idx = i;
            }
            cmb->setCurrentIndex(idx);
            return;
        }
    }
    QItemDelegate::setEditorData(editor, index);
}

void ComboDelegate::setModelData(QWidget *editor,
                     QAbstractItemModel *model,
                     const QModelIndex &index) const
{
    if (!editor->metaObject()->userProperty().isValid()) {
        QComboBox *cmb = static_cast<QComboBox*>(editor);
        QVariant value = cmb->itemData(cmb->currentIndex(), Qt::UserRole);
        if (value.isValid()) {
            model->setData(index, value);
            return;
        }
    }
    QItemDelegate::setModelData(editor, model, index);
}

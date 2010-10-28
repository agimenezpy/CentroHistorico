#include "combodelegate.h"
#include <QtGui/QComboBox>
#include <QMetaProperty>

ComboDelegate::ComboDelegate(QObject *parent) : QItemDelegate(parent) {}

void ComboDelegate::setEditorData(QWidget *editor,
                       const QModelIndex &index) const
{
    if (!editor->metaObject()->userProperty().isValid()) {
        if (editor->property("currentIndex").isValid()) {
            QComboBox *cmb = (QComboBox*) editor;
            int i = 0;
            for (i = 0; i < cmb->count(); i++) {
                if (index.data() == cmb->itemData(i, Qt::UserRole))
                    break;
            }
            cmb->setCurrentIndex(i);
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
        QComboBox *cmb = (QComboBox*) editor;
        QVariant value = cmb->itemData(cmb->currentIndex(), Qt::UserRole);
        if (value.isValid()) {
            model->setData(index, value);
            return;
        }
    }
    QItemDelegate::setModelData(editor, model, index);
}

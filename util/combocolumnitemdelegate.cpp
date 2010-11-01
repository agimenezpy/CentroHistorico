#include "combocolumnitemdelegate.h"
#include <QTableWidget>
#include <QComboBox>
#include <QMetaProperty>
#include <QLabel>

ComboColumnItemDelegate::ComboColumnItemDelegate(QMap<QString, QVariant>* data, QWidget* parent)
    : QItemDelegate(parent) {
    pairs = data;
}

ComboColumnItemDelegate::~ComboColumnItemDelegate() {
    delete pairs;
}

QWidget *ComboColumnItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                          const QModelIndex &index) const {
    QComboBox* cmb = new QComboBox(parent);
    cmb->addItem("Ninguno");
    foreach (QString clave, pairs->keys()) {
        cmb->addItem(clave, pairs->value(clave));
    }
    return cmb;
}

void ComboColumnItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    if (!editor->metaObject()->userProperty().isValid()) {
        if (editor->property("currentIndex").isValid()) {
            QComboBox *cmb = static_cast<QComboBox*>(editor);
            int i;
            for (i = 1; i < cmb->count(); i++) {
                if (index.model()->data(index, Qt::UserRole) == cmb->itemData(i, Qt::UserRole))
                    break;
            }
            if (i < cmb->count()) {
                cmb->setCurrentIndex(i);
            }
            else
                cmb->setCurrentIndex(0);
            return;
        }
    }
    QItemDelegate::setEditorData(editor, index);
}

void ComboColumnItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                      const QModelIndex &index) const {
    QComboBox *cmb = static_cast<QComboBox*>(editor);
    if (cmb->currentIndex() != 0) {
        model->setData(index, cmb->itemData(cmb->currentIndex(), Qt::UserRole), Qt::UserRole);
        model->setData(index, cmb->itemText(cmb->currentIndex()), Qt::DisplayRole);
    }
    else {
        model->setData(index, QChar('\0'), Qt::UserRole);
        model->setData(index, "", Qt::DisplayRole);
    }
}

void ComboColumnItemDelegate::updateEditorGeometry(QWidget *editor,
                                              const QStyleOptionViewItem &option, const QModelIndex &index) const {
    editor->setGeometry(option.rect);
}

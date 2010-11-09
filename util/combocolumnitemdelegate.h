#ifndef COMBOCOLUMNITEMDELEGATE_H
#define COMBOCOLUMNITEMDELEGATE_H

#include <QItemDelegate>
#include <QString>
#include <QVariant>
#include <QMap>

class QComboBox;

class ComboColumnItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ComboColumnItemDelegate(QMap<QString, QVariant> *data, QWidget* parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    QMap<QString, QVariant> *pairs;
};

#endif // COMBOCOLUMNITEMDELEGATE_H

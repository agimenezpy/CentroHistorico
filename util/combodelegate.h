#ifndef COMBODELEGATE_H
#define COMBODELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QAbstractItemModel>
class QWidget;
class QObject;

class ComboDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ComboDelegate(QObject *parent = 0);
    void setEditorData(QWidget *editor,
                      const QModelIndex &index) const;
    void setModelData(QWidget *editor,
                     QAbstractItemModel *model,
                     const QModelIndex &index) const;

};

#endif // COMBODELEGATE_H

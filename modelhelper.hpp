#ifndef MODELHELPER_HPP
#define MODELHELPER_HPP

#include <QtCore/QString>

class QSqlTableModel;
class QDataWidgetMapper;
class QWidget;

class ModelHelper {
public:
    void submit();
    void revert();

protected:
    QSqlTableModel *model;
    QDataWidgetMapper *mapper;
    bool isNew;
    void construct(QWidget* parent, QString tableName, QString column);
    void init();

};

#endif // MODELHELPER_HPP
#ifndef UTIL_H
#define UTIL_H
inline int generateId(const QString &table)
{
    QSqlQuery query;
    query.exec("SELECT MAX(id) FROM " + table);
    int id = 0;
    if (query.next())
        id = query.value(0).toInt() + 1;
    return id;
}

inline bool exist(const QString &table, const QString column, const QString value) {
    QSqlQuery query;
    query.prepare(QString("SELECT count(%1) FROM %2 WHERE %1 = ?").arg(column, table));
    query.addBindValue(value);
    query.exec();
    query.next();
    int count = query.value(0).toInt();
    return count > 0;
}
#endif // UTIL_H

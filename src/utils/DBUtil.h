#ifndef DBUTIL_H
#define DBUTIL_H

//for database query
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QTextCodec>

class DBUtil
{
public:
    DBUtil();

public:
    int createDbAndTables(); //创建数据库和相应的表
    QVariant query();
    int insert();
    int update();

    QString loadSql(QString fileName);
};

#endif // DBUTIL_H

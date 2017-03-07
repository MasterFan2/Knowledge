#include "DBUtil.h"

DBUtil::DBUtil()
{

}

//加载数据库脚本文件
QString DBUtil::loadSql(QString fileName)
{
    QFile file(fileName);
    QString str;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
         QByteArray bytes = file.readAll();
         QTextCodec *codec = QTextCodec::codecForName("utf-8");
         if(codec)
              str = codec->toUnicode(bytes);
    }
    return str;
}

//创建数据库
int DBUtil::createDb()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("knowledge.db");

    if (database.open())
    {
        QSqlQuery query;

        qDebug() << "database opened";

        QString create_widget_sql       = loadSql(":/conf/res/create_table_widget.sql");       //创建组件表
        QString create_project_dir_sql  = loadSql(":/conf/res/create_table_projectdir.sql");   //创建项目目录表
        QString create_project_file_sql = loadSql(":/conf/res/create_table_project_file.sql"); //创建文件表
        QString create_sdk_sql          = loadSql(":/conf/res/create_table_sdk.sql");          //创建sdk表


        query.prepare(create_widget_sql); //创建表

        if(!query.exec())//1创建组件表
        {
            qDebug()<<QObject::tr("创建组件表 failed");
            qDebug()<< "error:" << query.lastError();
        }else
        {
            qDebug()<<QObject::tr("创建组件表 success");
        }


        query.prepare(create_project_dir_sql);
        if(!query.exec())//2创建项目目录表
        {
            qDebug()<<QObject::tr("创建项目目录表 failed");
            qDebug()<< "error:" << query.lastError();
        }else
        {
            qDebug()<<QObject::tr("创建项目目录表 success");
        }

        query.prepare(create_project_file_sql);
        if(!query.exec())//3创建文件表
        {
            qDebug()<<QObject::tr("创建文件表 failed");
            qDebug()<< "error:" << query.lastError();
        }else
        {
            qDebug()<<QObject::tr("创建文件表 success");
        }

        query.prepare(create_sdk_sql);
        if(!query.exec())//4创建sdk表
        {
            qDebug()<<QObject::tr("创建sdk表 failed");
            qDebug()<< "error:" << query.lastError();
        }else
        {
            qDebug()<<QObject::tr("创建sdk表 success");
        }

        query.clear();
    }else
    {
        qDebug()<<QObject::tr("Table open failed");
    }

    if(database.isOpen()) {
        database.close();
    }
}

QVariant DBUtil::query()
{

}

int DBUtil::insert()
{

}

int DBUtil::update()
{

}

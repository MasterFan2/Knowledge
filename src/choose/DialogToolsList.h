#ifndef DIALOGTOOLSLIST_H
#define DIALOGTOOLSLIST_H

#include <QDebug>

#include <QDialog>
#include "../bean/WidgetBean.h"

//for database query
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

namespace Ui {
class DialogToolsList;
}

class DialogToolsList : public QDialog
{
    Q_OBJECT

public:
    explicit DialogToolsList(QWidget *parent = 0);
    ~DialogToolsList();

signals:
    void onChooseData(QList<WidgetBean*> dataList);//返回选择的数据集

private:
    Ui::DialogToolsList *ui;
    QList<WidgetBean*> widgetList;

private:
    void queryWidgetListByDatabase();//查询所有数据
    void checkChooseItems();         //检测发

private slots:
    void onDoneClick();//点击完成按钮
};

#endif // DIALOGTOOLSLIST_H

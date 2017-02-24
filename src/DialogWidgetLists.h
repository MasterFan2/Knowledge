/*************************************
 * 选择组件的列表展示窗口
 * create by masterFan on 2016-02-23
 ************************************/
#ifndef DIALOGWIDGETLISTS_H
#define DIALOGWIDGETLISTS_H

#include <QDialog>
#include <QDebug>

//for database query
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

//bean
#include "bean/WidgetBean.h"

namespace Ui {
class DialogWidgetLists;
}

class DialogWidgetLists : public QDialog
{
    Q_OBJECT

public:
    explicit DialogWidgetLists(QWidget *parent = 0);
    ~DialogWidgetLists();

signals:
    void onChooseData(QList<WidgetBean*> dataList);//返回选择的数据集

/**------------------------
 * variable
 *------------------------*/
private:
    Ui::DialogWidgetLists *ui;
    QList<WidgetBean*> widgetList;

/************************
 * function
 ***********************/
private:
    void queryWidgetListByDatabase();//查询所有数据
    void checkChooseItems();         //检测发



private slots:
    void onDoneClick();//点击完成按钮
};

#endif // DIALOGWIDGETLISTS_H

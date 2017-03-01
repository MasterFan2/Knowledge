#include "DialogToolsList.h"
#include "ui_DialogToolsList.h"
#include "../item/ItemWidgetListForm.h"

DialogToolsList::DialogToolsList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogToolsList)
{
    ui->setupUi(this);
    //关闭窗口上的问号按钮
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);

    queryWidgetListByDatabase();

    ///connect clicked
    connect(ui->doneBtn, SIGNAL(clicked()), this, SLOT(onDoneClick()));
}

//查询数据库
void DialogToolsList::queryWidgetListByDatabase()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("knowledge.db");
    QSqlQuery query;
    QString select_all_sql = "select * from widget where type=1";

    if (database.open())
    {
        //查询所有记录
        query.prepare(select_all_sql);
        if(!query.exec())
        {
            qDebug()<< "query error:" << query.lastError();
        }
        else
        {
            while(query.next())
            { //id, name, path, description, permissions, type, remark
                WidgetBean* widgetBean = new WidgetBean();


                int id = query.value(0).toInt();
                widgetBean->setId(id);

                QString name = query.value(1).toString();
                widgetBean->setName(name);

                QString path = query.value(2).toString();
                widgetBean->setPath(path);

                QString description = query.value(3).toString();
                widgetBean->setDescription(description);

                QString permissions = query.value(4).toString();
                widgetBean->setPermisions(permissions);

                int type = query.value(5).toInt();
                widgetBean->setType(type);

                QString remark = query.value(6).toString();
                widgetBean->setRemark(remark);

                widgetList.append(widgetBean);

                ///set ListWidget item
                QListWidgetItem *item = new QListWidgetItem();
                ui->listWidget->addItem(item);

                ItemWidgetListForm *myItem = new ItemWidgetListForm(ui->listWidget);
                myItem->show();
                ui->listWidget->setItemWidget(item, myItem);
                myItem->setUiData(widgetBean);

                item->setSizeHint(QSize(myItem->rect().width(), myItem->rect().height()));
            }

//            for (WidgetBean* bean : widgetList)
//            {
//                qDebug()<<QString("ID:%1  Name:%2  Path:%3 description:%4 permissions:%5 type:%6 remark:%7").arg(bean->id())
//                          .arg(bean->name()).arg(bean->path()).arg(bean->description()).arg(bean->permisions()).arg(bean->type()).arg(bean->remark());
//            }
        }

        query.clear();
        database.close();
    }
    else
    {
        qDebug() << "database open error!";
    }
}

//点击完成按钮, 过滤选择的项， 把数据返回
void DialogToolsList::onDoneClick()
{
    QList<WidgetBean*> checkedList;
    int size = ui->listWidget->count();
    for (int i=0; i < size; i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        ItemWidgetListForm *widget = (ItemWidgetListForm *) ui->listWidget->itemWidget(item);
        if (widget->checkBox()->isChecked())
        {
            checkedList.append(widgetList.at(i));
        }
    }

    if (checkedList.size() > 0)
    {
        setResult(QDialog::Accepted);//1
        emit onChooseData(checkedList);

        accept();
    }
    else
    {
        setResult(QDialog::Rejected);//0
        reject();
    }
}

DialogToolsList::~DialogToolsList()
{
    delete ui;
}

#include "DialogGeneratePro.h"
#include "ui_DialogGeneratePro.h"
#include <QListWidgetItem>
#include <QStringList>

//SQLite   在.pro文件中添加 QT += sql
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

#include <QDir>


DialogGeneratePro::DialogGeneratePro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGeneratePro)
{
    ui->setupUi(this);

    //关闭窗口上的问号按钮
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);

    ui->stackedWidget->setCurrentIndex(0);//设置默认显示卡页
    checkWidget();//禁用button

    initialzie();//初始化数据

    dialogWidgetLists = new DialogWidgetLists(this);
    connect(dialogWidgetLists, SIGNAL(onChooseData(QList<WidgetBean*>)), this, SLOT(receiveChooseList(QList<WidgetBean*>)));

    //添加点击事件
    connect(ui->previousBtn, SIGNAL(clicked()), this, SLOT(onPreviousClicked()));
    connect(ui->nextBtn,     SIGNAL(clicked()), this, SLOT(onNextClicked()));
    connect(ui->doneBtn,     SIGNAL(clicked()), this, SLOT(onDoneClicked()));

    //数据库操作
    connect(ui->step3addBtn,    SIGNAL(clicked()), this, SLOT(sqliteAdd()));
    connect(ui->step3delBtn,    SIGNAL(clicked()), this, SLOT(sqliteDel()));
    connect(ui->step3updateBtn, SIGNAL(clicked()), this, SLOT(sqliteUpdate()));
    connect(ui->step3queryBtn,  SIGNAL(clicked()), this, SLOT(sqliteQuery()));

    //选择widgets
    connect(ui->step3ChooseBtn, SIGNAL(clicked()), this, SLOT(chooseWidgetsByLists()));


}

void DialogGeneratePro::sqliteAdd()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("knowledge.db");

    if (database.open())
    {
        qDebug() << "database opened";
        QSqlQuery query;

        QString create_widget_sql = "create table widget (id int primary key not null, name varchar(100) not null, path varchar(100), description varchar(300) not null, permissions varchar(200), type int, remark varchar(300))"; //创建控件表

        QString insert_sql = "insert into widget(id, name, path, description, permissions, type, remark) values(?,?,?,?,?,?,?)";    //插入数据

        query.prepare(create_widget_sql); //创建表
        if(!query.exec())                 //查看创建表是否成功
        {
            qDebug()<<QObject::tr("Table Create failed");
            qDebug()<<query.lastError();
        }
        else
        {
            qDebug()<< "Table Created" ;
            query.prepare(insert_sql);

            QVariantList GroupIds;
            GroupIds.append(1);
            GroupIds.append(2);
            GroupIds.append(3);

            QVariantList GroupNames;
            GroupNames.append("下拉刷新");
            GroupNames.append("二维码");
            GroupNames.append("高德地图");

            QVariantList GroupPaths;
            GroupPaths.append("/effiction/pullRefresh.png");
            GroupPaths.append("/effiction/qrCoder.png");
            GroupPaths.append("/effiction/aliMap.png");


            QVariantList GroupDescriptions;
            GroupDescriptions.append("这是一个下拉刷新");
            GroupDescriptions.append("这是一个二维码");
            GroupDescriptions.append("这是高德地图");

            QVariantList GroupPermissionss;
            GroupPermissionss.append("Internet");
            GroupPermissionss.append("Camera");
            GroupPermissionss.append("Location");

            QVariantList GroupTypes;
            GroupTypes.append(0);
            GroupTypes.append(0);
            GroupTypes.append(1);

            QVariantList GroupRemarks;
            GroupRemarks.append("备注信息");
            GroupRemarks.append("备注信息");
            GroupRemarks.append("备注信息");

            query.addBindValue(GroupIds);
            query.addBindValue(GroupNames);
            query.addBindValue(GroupPaths);
            query.addBindValue(GroupDescriptions);
            query.addBindValue(GroupPermissionss);
            query.addBindValue(GroupTypes);
            query.addBindValue(GroupRemarks);



            if(!query.execBatch())
            {
                qDebug() << query.lastError();
            }
            else
            {
                qDebug() << "插入记录成功";
            }
        }

        database.close();
    }else {
        qDebug() << "database open error!";
    }
}

void DialogGeneratePro::sqliteDel()
{
    QDir *temp = new QDir;
    bool exists = temp->exists("./masterfan");
    if (exists)
    {
        qDebug()<< "dir exists:";
    }
    else
    {
        qDebug()<< "dir not exists:";

        if(temp->mkdir("./masterfan"))
        {
            qDebug()<< "dir created";
        }else
        {
            qDebug()<< "dir create error.";
        }
    }
}

//选择widget
//QDialog::Accepted   1
//QDialog::Rejected   0
void DialogGeneratePro::chooseWidgetsByLists()
{
    int result = dialogWidgetLists->exec();
    qDebug() << "选择Widgets::result=" << result;
}

void DialogGeneratePro::sqliteQuery()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("knowledge.db");
    QSqlQuery query;
    QString select_all_sql = "select * from widget where type=0";

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
                int id = query.value(0).toInt();
                QString name = query.value(1).toString();
                QString path = query.value(2).toString();
                QString description = query.value(3).toString();
                QString permissions = query.value(4).toString();
                int type = query.value(5).toInt();
                QString remark = query.value(6).toString();

                qDebug()<<QString("ID:%1  Name:%2  Path:%3 description:%4 permissions:%5 type:%6 remark:%7").arg(id)
                          .arg(name).arg(path).arg(description).arg(permissions).arg(type).arg(remark);
            }
        }

        database.close();
    }
    else
    {
        qDebug() << "database open error!";
    }
}

//接收返回数据
void DialogGeneratePro::receiveChooseList(QList<WidgetBean*> dataList)
{
    //===============显示第三步选择的列表=============
    ui->step3ListWidget->clear();
    int size = dataList.size();
    for(int i = 0; i < size; i ++)
    {
        QListWidgetItem *configButton = new QListWidgetItem(ui->step3ListWidget);
        configButton->setIcon(QIcon(dataList.at(i)->path()));
        configButton->setText(dataList.at(i)->name());
        configButton->setTextAlignment(Qt::AlignHCenter);
        configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);

        //ui->listWidget->setCurrentItem(configButton);
    }
    ui->step3ListWidget->setFlow(QListView::LeftToRight);
    ui->step3ListWidget->setResizeMode(QListView::Adjust);
    ui->step3ListWidget->update();
    qDebug() << "receiveChooseList:::dataSize=" << dataList.size();
}

void DialogGeneratePro::sqliteUpdate()
{

}

//初始化数据
void DialogGeneratePro::initialzie()
{
    //把头顶的toolbutton添加到QHsh中
    completeHash[0]=ui->toolButtonBase;
    completeHash[1]=ui->toolButtonChooseVersion;
    completeHash[2]=ui->toolButtonChooseWidget;
    completeHash[3]=ui->toolButtonChooseTools;

    //添加comboxBox的数据
    QStringList strList;
    strList << "API 9:Android 2.3 (Gingerbread)" << "API 10:Android 2.3.3 (Gingerbread)" << "API 11:Android 3.0 (Honeycomb)";
    ui->step2MinimunComboBox->addItems(strList);


    //===============显示第四步选择的列表=============
    ui->step4ListWidget->setResizeMode(QListView::Adjust);
    for(int i=0; i<15; i++)
    {
        QListWidgetItem *configButton = new QListWidgetItem(ui->step4ListWidget);
        configButton->setIcon(QIcon(":/images/res/gen.png"));
        configButton->setText(tr("Master Fan"));
        configButton->setTextAlignment(Qt::AlignHCenter);
        configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);


        //ui->listWidget->setCurrentItem(configButton);
    }
    ui->step4ListWidget->setFlow(QListView::LeftToRight);
    ui->step4ListWidget->update();
}

//改变已完成按钮的显示状态
void DialogGeneratePro::changeButtonState(int completeIndex, int oldIndex)
{
    completeHash[completeIndex]->setIcon(QIcon(":/images/res/icon_success.png"));
}

 // 禁用控件
void DialogGeneratePro::checkWidget()
{
    ui->previousBtn->setEnabled(false);
    ui->doneBtn->setEnabled(false);
}

//上一步按钮点击
void DialogGeneratePro::onPreviousClicked()
{
     if (currentIndex == 0)//在第一步， 无法再上一步了
     {
         ui->previousBtn->setEnabled(false);
     }
     else if (currentIndex > 0)
     {
         currentIndex --;
         ui->stackedWidget->setCurrentIndex(currentIndex);
         ui->doneBtn->setEnabled(false);
         if (currentIndex == 0) ui->previousBtn->setEnabled(false);
         else                   ui->nextBtn->setEnabled(true);
     }
}

//下一步
void DialogGeneratePro::onNextClicked()
{
    if (currentIndex < 3)//第一次
    {
        currentIndex ++;
        changeButtonState(currentIndex - 1, currentIndex - 1);
        ui->stackedWidget->setCurrentIndex(currentIndex);
        ui->previousBtn->setEnabled(true);
        if (currentIndex == 3)
        {
            ui->nextBtn->setEnabled(false);
            ui->doneBtn->setEnabled(true);
        }
    }
}

//完成
void DialogGeneratePro::onDoneClicked()
{
    qDebug() << "done clicked";
}

//检查当前步骤是否完成
bool DialogGeneratePro::checkVariableComplete(int index)
{

    return true;
}

//destroy
DialogGeneratePro::~DialogGeneratePro()
{
    delete ui;
}

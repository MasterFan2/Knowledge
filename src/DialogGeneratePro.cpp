/***********************************************************
 * 生成项目选择流程的主窗口
 * 目前所有选择项保存在内存中， 选择完成后能过读取保存的信息开始生成项目
 * [后期考虑把选择的配置放到一个配置文件中]
 *
 * create by MasterFan
 *      on 2017年2月25日10:29:31
 *
 *
 *
 ***********************************************************/

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
#include <QColor>

//temp
#include <QMovie>

//constructor
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
    disableWidget();//禁用button

    initialzie();//初始化数据

    conf = new ConfBean();

    //设置提示文字红色
    QPalette pa;
    pa.setColor(QPalette::WindowText, QColor(254, 123, 122));
    ui->labelWarnning->setPalette(pa);

    dialogWidgetLists = new DialogWidgetLists(this);
    dialogToolList    = new DialogToolsList(this);

    QMovie *wait = new QMovie(":/images/res/processing.gif");
    ui->labelWaitting->setMovie(wait);
    wait->start();


    //添加点击事件
    connect(ui->previousBtn, SIGNAL(clicked()), this, SLOT(onPreviousClicked()));
    connect(ui->nextBtn,     SIGNAL(clicked()), this, SLOT(onNextClicked()));
    connect(ui->doneBtn,     SIGNAL(clicked()), this, SLOT(onDoneClicked()));

    //数据库操作
    connect(ui->step3addBtn,    SIGNAL(clicked()), this, SLOT(sqliteAdd()));
    connect(ui->step3delBtn,    SIGNAL(clicked()), this, SLOT(sqliteDel()));
    connect(ui->step3updateBtn, SIGNAL(clicked()), this, SLOT(sqliteUpdate()));
    connect(ui->step3queryBtn,  SIGNAL(clicked()), this, SLOT(sqliteQuery()));

    //step1  选择workspace
    connect(ui->chooseWorkspaceBtn,  SIGNAL(clicked()), this, SLOT(chooseWorkspace()));

    //选择widgets 和 tools
    connect(ui->step3ChooseBtn, SIGNAL(clicked()), this, SLOT(chooseWidgetsByLists()));
    connect(ui->step4ChooseBtn, SIGNAL(clicked()), this, SLOT(chooseToolsByList()));

    //处理选择widgets和tools回调
    connect(dialogWidgetLists, SIGNAL(onChooseData(QList<WidgetBean*>)), this, SLOT(receiveChooseList(QList<WidgetBean*>)));
    connect(dialogToolList,    SIGNAL(onChooseData(QList<WidgetBean*>)), this, SLOT(receiveChooseTools(QList<WidgetBean*>)));

    //步骤点击按钮跳转对应的界面
    connect(ui->toolButtonBase,          SIGNAL(clicked()), this, SLOT(step1()));
    connect(ui->toolButtonChooseVersion, SIGNAL(clicked()), this, SLOT(step2()));
    connect(ui->toolButtonChooseWidget,  SIGNAL(clicked()), this, SLOT(step3()));
    connect(ui->toolButtonChooseTools,   SIGNAL(clicked()), this, SLOT(step4()));
}

//选择工具
void DialogGeneratePro::chooseToolsByList()
{
    dialogToolList->exec();
}

//接收返回tools
void DialogGeneratePro::receiveChooseTools(QList<WidgetToolBean*> dataList)
{
    //===============显示第四步选择的列表=============
    ui->step4ListWidget->clear();
    int size = dataList.size();
    for(int i = 0; i < size; i ++)
    {
        QListWidgetItem *configButton = new QListWidgetItem(ui->step4ListWidget);
        configButton->setIcon(QIcon(dataList.at(i)->previewpath));
        configButton->setText(dataList.at(i)->name);
        configButton->setTextAlignment(Qt::AlignHCenter);
        configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);

        //ui->listWidget->setCurrentItem(configButton);
    }
    ui->step4ListWidget->setFlow(QListView::LeftToRight);
    ui->step4ListWidget->setResizeMode(QListView::Adjust);
    ui->step4ListWidget->update();

//    qDebug() << "receiveChooseList:::dataSize=" << dataList.size();
    conf->toolList = dataList;
}

//添加到数据库中
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


//从数据库中删除
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
        }
        else
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

//接收返回数据[组件]
void DialogGeneratePro::receiveChooseList(QList<WidgetToolBean*> dataList)
{
    //===============显示第三步选择的列表=============
    ui->step3ListWidget->clear();
    int size = dataList.size();
    for(int i = 0; i < size; i ++)
    {
        QListWidgetItem *configButton = new QListWidgetItem(ui->step3ListWidget);
        configButton->setIcon(QIcon(dataList.at(i)->previewpath));
        configButton->setText(dataList.at(i)->name);
        configButton->setTextAlignment(Qt::AlignHCenter);
        configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);

        //ui->listWidget->setCurrentItem(configButton);
    }
    ui->step3ListWidget->setFlow(QListView::LeftToRight);
    ui->step3ListWidget->setResizeMode(QListView::Adjust);
    ui->step3ListWidget->update();
    qDebug() << "receiveChooseList:::dataSize=" << dataList.size();

    conf->widgetList = dataList;
}

//更新数据库
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

    //添加comboxBox的数据 [版本选择]
    QStringList strList;
    strList << "API 9:Android 2.3 (Gingerbread)" << "API 10:Android 2.3.3 (Gingerbread)" << "API 11:Android 3.0 (Honeycomb)";
    ui->step2MinimunComboBox->addItems(strList);

    QStringList sdkList;
    sdkList << "API 9:Android 2.3 (Gingerbread)" << "API 10:Android 2.3.3 (Gingerbread)" << "API 11:Android 3.0 (Honeycomb)";
    ui->step2targetCBox->addItems(sdkList);

    QStringList gradleList;
    gradleList << "2.1.2" << "2.2.2"  << "2.3.0alpha";
    ui->step2GradleCBox->addItems(gradleList);
}

//改变已完成按钮的显示状态
void DialogGeneratePro::changeButtonState(int completeIndex, int oldIndex)
{
    completeHash[completeIndex]->setIcon(QIcon(":/images/res/icon_success.png"));
    completeHash[completeIndex + 1]->setChecked(true);
}

 // 禁用控件
void DialogGeneratePro::disableWidget()
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

//检查当前步骤是否选择完整
int DialogGeneratePro::checkCurrentStep(int currentIndex)
{
    conf->applicationName = ui->lineEditAppName->text();
    conf->packageName     = ui->lineEditPkgName->text();

    if (currentIndex == 0)
    {
        if (conf->applicationName.isEmpty()) return 1;//BaseChoose::NotSetProjectName;
        if (conf->packageName.isEmpty())     return 2;//BaseChoose::NotSetPackageName;
        if (conf->workspace.isEmpty())       return 3;//BaseChoose::NotSetWorkspace;
                                             return 0;//BaseChoose::Done;
    }
    else if(currentIndex == 1)
    {
        return 0;//BaseChoose::Done;
    }
    else return 0;//BaseChoose::Done;
}

//下一步
void DialogGeneratePro::onNextClicked()
{
    if (currentIndex == 0 ) {
        int chooseResult = checkCurrentStep(0);
        if (chooseResult != 0) {
            if (chooseResult == 1)
            {
                ui->labelWarnning->setText("请输入项目名称");
                return;
            }

            if (chooseResult == 2)
            {
                ui->labelWarnning->setText("请输入包名称");
                return;
            }

            if (chooseResult == 3)
            {
                ui->labelWarnning->setText("请选择保存路径");
                return;
            }
        }
        ui->labelWarnning->setText("");
    }
    else if(currentIndex == 1) //选择一些版本
    {
        conf->minimunVersion    = 11;
        conf->targetVersion     = "24";
        conf->compileSdkVersion = 24;
        conf->toolsBuild        = "2.2.2";
        conf->hasLibSo          = false;
        conf->buildToolsVersion = "" + conf->targetVersion + ".0.0";
    }

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

//顶部的步骤按钮点击slots
void DialogGeneratePro::step1()//第一步
{
    currentIndex = 0;
    ui->previousBtn->setEnabled(false);
    ui->nextBtn->setEnabled(true);
    ui->stackedWidget->setCurrentIndex(0);
}

void DialogGeneratePro::step2()
{
    currentIndex = 1;
    ui->previousBtn->setEnabled(true);
    ui->nextBtn->setEnabled(true);
    ui->stackedWidget->setCurrentIndex(1);
}

void DialogGeneratePro::step3()
{
    currentIndex = 2;
    ui->previousBtn->setEnabled(true);
    ui->nextBtn->setEnabled(true);
    ui->stackedWidget->setCurrentIndex(2);
}

void DialogGeneratePro::step4()
{
    currentIndex = 3;
    ui->previousBtn->setEnabled(true);
    ui->nextBtn->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(3);
}

/***********************
 * @desc 选择工作空间目录【step 1】
 *
 *
 * @auther masterFan
 * @date 2017年3月2日
 * @return
 **********************/
void DialogGeneratePro::chooseWorkspace()
{
    QString workspacePath = QFileDialog::getExistingDirectory(this,"请选择模板保存路径...","/");
    if(!workspacePath.isEmpty())
    {
//        qDebug() << "Dir:" << workspacePath + "/";
        conf->workspace = workspacePath + "/";
        ui->labelPath->setText(conf->workspace);
    }
    else
    {
        qDebug() << "Not choose workspace.";
    }
//    QString fileName = QFileDialog::getOp(this, tr("选择文件"), "/", tr("All Files (*);;Text Files(*.txt)"), &selectedFilter, options);

}

//destroy
DialogGeneratePro::~DialogGeneratePro()
{
    delete ui;
}

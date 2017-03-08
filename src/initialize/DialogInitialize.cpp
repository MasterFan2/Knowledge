/***********************************************************
 * 程序运行前的初始化，主要处理工作如下：
 * 1.生成项目运行过程中用到的一些文件夹
 *  【预览图】【gif动态效果】【java源文件】【res资源文件】【配置文件】
 *
 * 2.数据库创建，表创建
 *
 * create by MasterFan
 *          on 2017年3月7日
 *
 ***********************************************************/

#include "DialogInitialize.h"
#include "ui_DialogInitialize.h"
#include <QDir>
#include <QFile>
#include <QIODevice>

#include <QThread>

DialogInitialize::DialogInitialize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInitialize)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏 
    
    //播放gif动画
    QMovie *progress = new QMovie(":/images/res/processing.gif");
    ui->labelGif->setMovie(progress);
    progress->start();

    //设置背景颜色
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255, 255, 255));
    setPalette(palette);

    //创建数据库
    dbUtil = new DBUtil();
    dbUtil->createDbAndTables();

    createSuccessFile();//设置初始化完成标识

    QStringList lists;
    lists << "./java" << "./layout" << "./image" ;
    createFolders(lists);
}

//为了方便， 初始化完成后创建一个文件，表示已经初始化过了。
void DialogInitialize::createSuccessFile()
{
    QString successDir = "./conf/";
    QString successFile = successDir + "success.cmd";

    QDir *dir = new QDir();
    QFile file(successFile);

    if (!dir->exists(successDir))  dir->mkdir(successDir);
    if (!file.exists()) file.open(QIODevice::WriteOnly);

}

//创建一些资源文件的目录，如：gif/preview
void DialogInitialize::createFolders(QStringList lists)
{
    QDir* dir;
    for (QString folder : lists)
    {
        dir = new QDir();
        if (!dir->exists(folder)) dir->mkdir(folder);
        delete dir;
    }
}

DialogInitialize::~DialogInitialize()
{
    delete ui;
}

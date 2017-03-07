#include "DialogInitialize.h"
#include "ui_DialogInitialize.h"

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

    dbUtil = new DBUtil();

    dbUtil->createDb();
}

DialogInitialize::~DialogInitialize()
{
    delete ui;
}

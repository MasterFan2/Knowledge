#include "DialogInitialize.h"
#include "ui_DialogInitialize.h"

DialogInitialize::DialogInitialize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInitialize)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏 
    
    QMovie *progress = new QMovie(":/images/res/progress.gif");
    ui->labelGif->setMovie(progress);
    progress->start();

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255, 255, 255));
    setPalette(palette);
}

DialogInitialize::~DialogInitialize()
{
    delete ui;
}
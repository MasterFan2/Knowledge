#include "ItemWidgetListForm.h"
#include "ui_ItemWidgetListForm.h"

ItemWidgetListForm::ItemWidgetListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemWidgetListForm)
{
    ui->setupUi(this);
}

void ItemWidgetListForm::setUiData(WidgetBean* bean) //设置item的数据
{
    QString efficient = bean->path();
    if (efficient == NULL)
    {
//        ui->labelIcon->setPixmap(QPixmap(":/images/res/icon_default.png"));new QMovie(
         ui->labelIcon->setMovie(new QMovie("./masterfan/refresh.gif"));
    }
    else if (efficient.endsWith(".png") || efficient.endsWith(".bmp") || efficient.endsWith(".jpg"))
    {
        ui->labelIcon->setPixmap(QPixmap(bean->path()));
    }
    else if (efficient.endsWith(".gif") || efficient.endsWith(".mp4"))
    {
        ui->labelIcon->setMovie(new QMovie(bean->path()));
    }

    ui->labelName->setText(bean->name());
    ui->labelDescription->setText(bean->description());
    ui->labelRemark->setText(bean->remark());
}

QCheckBox* ItemWidgetListForm::checkBox()
{
    return ui->checkBox;
}

ItemWidgetListForm::~ItemWidgetListForm()
{
    delete ui;
}
